#include <ctime>
#include <sstream>
#include <stdexcept>

#include "APacketServer.hpp"
#include "MapDB.hpp"
#include "json.hpp"

std::size_t APacketServer::id = 0;

APacketServer::APacketServer(boost::asio::io_service &ioService, int port, std::string const &cookie, IDataBase *db)
    : AUdpServer(ioService, port),
      _db(db),
      _cookie(cookie),
      _packetManager(
        this->_db,
        [this](Packet &packet) { this->packetHandler(packet); },
        [this](Packet &packet) { this->encryptor(packet); },
        [this](Packet &packet, boost::asio::ip::udp::endpoint &from) { return this->sendSuccess(packet, from); }
      ),
      _resolver(ioService),
      _reserveChecker(ioService, 5, [this](boost::system::error_code const &ec) { this->checkReserve(ec); })
{
    this->_reserveChecker.start();
    this->_crypt = nullptr;
}

APacketServer::~APacketServer() {
    delete this->_db;
    this->_reserveChecker.stop();
}

void APacketServer::sendPacket(std::string const &data,
                               boost::asio::ip::udp::endpoint const &to,
                               std::string const &id,
                               bool force,
                               bool reserve) {
    Packet packet;

    packet.set(Packet::Field::ID, id);
    packet.set(Packet::Field::COOKIE, this->_cookie);
    packet.set(Packet::Field::DATA, this->_crypt ? this->_crypt->encrypt(data) : data);
    std::vector<Packet> packets = packet.split();
    if (reserve) {
        this->reservePackets(packets, to);
    }
    if (!force && this->isIgnited(packet.getPtree(), to)) {
        return ;
    }
    try {
        for (auto &part : packets) {
            std::string msg(std::move(part.stringify()));
            this->_socket.send_to(boost::asio::buffer(msg, msg.length()), to);
        }
    } catch (boost::system::system_error const &ec) {
    }
}

void APacketServer::sendPacket(std::string const &data,
                               boost::asio::ip::udp::endpoint &to,
                               bool force,
                               bool reserve) {
    this->sendPacket(data, to, std::to_string(APacketServer::id++), reserve);
}

void APacketServer::requestHandler(boost::system::error_code ec,
                                   std::string req,
                                   boost::asio::ip::udp::endpoint clientEndpoint) {
    std::size_t index = req.find_last_not_of("\n\r");
    req.resize(index);
    if (this->requestCheck(ec, req, clientEndpoint)) {
        this->_packetManager.in(req, clientEndpoint);
    }
}

void APacketServer::saveClient(std::string const &cookie, boost::asio::ip::udp::endpoint const &from) {
    boost::property_tree::ptree ptree;
    ptree.put("cookie", cookie);
    try {
        auto client = this->_db->findOne("client", ptree);
        client.put("host", from.address().to_string());
        client.put("port", from.port());
        this->_db->update("client", ptree, client);
    } catch (std::exception &err) {
        ptree.put("host", from.address().to_string());
        ptree.put("port", from.port());
        this->_db->insert("client", ptree);
    }
}

void APacketServer::sendSuccess(Packet &packet, boost::asio::ip::udp::endpoint &from) {
    this->saveClient(packet.getPtree().get(Packet::fields.at(Packet::Field::COOKIE), ""), from);
    boost::property_tree::ptree ptree;
    ptree.put("type", "success");
    ptree.put(Packet::fields.at(Packet::Field::ID), packet.getPtree().get(Packet::fields.at(Packet::Field::ID), ""));
    ptree.put(Packet::fields.at(Packet::Field::PART), packet.getPtree().get(Packet::fields.at(Packet::Field::PART), ""));
    this->sendPacket(json::stringify(ptree), from, false);
}

void APacketServer::setDB(IDataBase *db) {
    if (this->_db) {
        delete this->_db;
    }
    this->_db = db;
    this->_packetManager.setDB(db);
}

void APacketServer::setCrypt(ICrypt *crypt) {
    this->_crypt = crypt;
    this->_packetManager.setCrypt(crypt);
}

void APacketServer::reservePackets(std::vector<Packet> const &packets, boost::asio::ip::udp::endpoint const &to) {
    for (auto part : packets) {
        boost::property_tree::ptree ptree;
        ptree.put("host", to.address().to_string());
        ptree.put("port", to.port());
        ptree.put_child("packet", part.getPtree());
        this->_db->update(PacketManager::waitingColName, ptree, ptree, true);
        auto vec = this->_db->find(PacketManager::waitingColName, {});
    }
}

void APacketServer::checkReserve(boost::system::error_code const &) {
    auto packets = this->_db->find(PacketManager::waitingColName, {});
    if (!packets.size()) {
        return ;
    }
    for (auto &part : packets) {
        std::string host = part.get("host", "");
        std::string port = part.get("port", "");
        boost::asio::ip::udp::endpoint endpoint = *this->_resolver.resolve({boost::asio::ip::udp::v4(), host, port});
        try {
            if (!this->isIgnited(part.get_child("packet"), endpoint)) {
                continue ;
            }
            std::string msg(std::move(json::stringify(part.get_child("packet"))));
                this->_socket.send_to(boost::asio::buffer(msg, msg.length()), endpoint);
        } catch (std::exception &err) {
        }
    }
}
