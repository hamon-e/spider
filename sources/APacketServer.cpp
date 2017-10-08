#include <ctime>
#include <sstream>
#include <stdexcept>

#include "APacketServer.hpp"
#include "MapDB.hpp"
#include "json.hpp"

std::string const APacketServer::waitingColName = "waiting";
std::size_t APacketServer::id = 0;

APacketServer::APacketServer(boost::asio::io_service &ioService, int port, IDataBase *db)
    : AUdpServer(ioService, port),
      _db(db),
      _packetManager(
        *this->_db,
        [this](Packet &packet) { this->packetHandler(packet); },
        [this](Packet &packet, boost::asio::ip::udp::endpoint &from) { return this->sendSuccess(packet, from); }
      ),
      _resolver(ioService),
      _network(true)
{}

void APacketServer::sendPacket(std::string const &cookie,
                               std::string const &data,
                               boost::asio::ip::udp::endpoint &to,
                               std::string const &id,
                               bool reserve) {
    Packet packet;

    packet.set(Packet::Field::ID, id);
    packet.set(Packet::Field::COOKIE, cookie);
    packet.set(Packet::Field::DATA, data);
    std::vector<Packet> packets = packet.split();
    if (reserve) {
        this->reservePackets(packets);
    }
    try {
        for (auto part : packets) {
            std::string msg(std::move(part.stringify()));
            std::cout << "sent : " << this->_socket.send_to(boost::asio::buffer(msg, msg.length()), to) << std::endl;
        }
    } catch (boost::system::system_error const &ec) {
    }
}

void APacketServer::sendPacket(std::string const &cookie,
                               std::string const &data,
                               boost::asio::ip::udp::endpoint &to,
                               bool reserve) {
    this->sendPacket(cookie, data, to, std::to_string(APacketServer::id++), reserve);
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

void APacketServer::sendSuccess(Packet &packet, boost::asio::ip::udp::endpoint &from) {
    std::cout << packet.getPtree().get("data", "caca") << std::endl;
    boost::property_tree::ptree ptree;
    ptree.put("type", "success");
    ptree.put(Packet::fields.at(Packet::Field::ID), packet.getPtree().get(Packet::fields.at(Packet::Field::ID), ""));
    ptree.put(Packet::fields.at(Packet::Field::PART), packet.getPtree().get(Packet::fields.at(Packet::Field::PART), ""));
    this->sendPacket("SERVER", json::stringify(ptree), from, false);
}

void APacketServer::reservePackets(std::vector<Packet> const &packets) {
    for (auto part : packets) {
        this->_db->insert(APacketServer::waitingColName, part.getPtree());
    }
}

void APacketServer::unreservePackets(std::string const &id) {
    boost::property_tree::ptree ptree;
    ptree.put(Packet::fields.at(Packet::Field::ID), id);
    this->_db->remove(APacketServer::waitingColName, ptree);
}

void APacketServer::unreservePackets(std::string const &id, std::size_t part) {
    boost::property_tree::ptree ptree;
    ptree.put(Packet::fields.at(Packet::Field::ID), id);
    ptree.put(Packet::fields.at(Packet::Field::PART), part);
    this->_db->remove(APacketServer::waitingColName, ptree);
}
