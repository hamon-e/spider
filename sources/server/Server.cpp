#include "LocalDB.hpp"
#include "MongoDB.hpp"
#include "Server.hpp"
#include "ssl/Base64.hpp"

Server::Server(boost::asio::io_service &ioService, int port)
  : APacketServer(ioService, port, new MongoDB()) {
    this->_crypt.init(this->_db);
    this->setCookie("SERVER");
}

bool Server::requestCheck(boost::system::error_code &,
                            std::string &,
                            boost::asio::ip::udp::endpoint &) {
    return true;
}

void Server::packetHandler(Packet &packet) {
    std::cout << "completed " << packet << std::endl;
    boost::property_tree::ptree ptree;
    boost::property_tree::read_json(packet.get<Packet::Field::DATA, std::string>(), ptree);
    if (ptree.get<std::string>("type") == "PublicKey") {
      this->_crypt.initAES(Base64::decrypt(ptree.get<std::string>("key")), packet.get<Packet::Field::COOKIE, std::string>());
    } else {
      this->_db->update(PacketManager::dataColName, packet.getPtree(), packet.getPtree(), true);
    }
}

void Server::encryptor(Packet &packet) {
  this->_crypt.encrypt(packet);
}

void Server::decryptor(Packet &packet) {
  this->_crypt.decrypt(packet);
}

bool Server::isIgnited(boost::property_tree::ptree const &, boost::asio::ip::udp::endpoint const &) const {
    return true;
}

void Server::send(std::string const &data,
		  std::string const &cookie) {
    boost::property_tree::ptree ptree;
    auto client = this->_db->findOne("client", ptree);

    std::string host = ptree.get<std::string>("host");
    std::string port = ptree.get<std::string>("port");

    boost::asio::ip::udp::endpoint endpoint = *this->_resolver.resolve({boost::asio::ip::udp::v4(), host, port});

    this->send(data, endpoint);
}

void Server::send(std::string const &data,
                  boost::asio::ip::udp::endpoint &clientEndpoint,
                  std::string const &id,
                  std::size_t size,
                  bool force) {
    this->sendPacket(data, clientEndpoint, id, size, force);
}

void Server::send(std::string const &data,
                  boost::asio::ip::udp::endpoint &clientEndpoint,
                  std::size_t size,
                  bool force) {
    this->sendPacket(data, clientEndpoint, size, force);
}
