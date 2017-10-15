#include "LocalDB.hpp"
#include "MongoDB.hpp"
#include "Server.hpp"
#include "ssl/Base64.hpp"

Server::Server(boost::asio::io_service &ioService, int port, IDataBase *db)
  : APacketServer(ioService, port, db) {
    this->_crypt.init(db);
    this->setCookie("SERVER");
}

bool Server::requestCheck(boost::system::error_code &,
                            std::string &,
                            boost::asio::ip::udp::endpoint &) {
    return true;
}

void Server::packetHandler(Packet &packet) {
  std::cout << packet << std::endl;
    boost::property_tree::ptree ptree = packet.getPtree();
    if (ptree.get<std::string>("data.type") == "PublicKey") {
      std::string cookie = ptree.get("cookie", "");
      this->send(this->_crypt.initAES(Base64::decrypt(ptree.get("data.key", "")), cookie),
		 cookie);
    } else {
      this->_db->update(PacketManager::dataColName, ptree, ptree, true);
    }
}

void Server::encryptor(Packet &packet, boost::asio::ip::udp::endpoint const &to) {
  this->_crypt.encrypt(packet, to.address().to_string(), std::to_string(to.port()));
}

std::string Server::encryptorMethod(Packet &packet, boost::asio::ip::udp::endpoint const &to) {
  return this->_crypt.encryptMethod(packet, to.address().to_string(), std::to_string(to.port()));
}

void Server::decryptor(Packet &packet) {
  this->_crypt.decrypt(packet);
}

void Server::send(std::string const &data,
		  std::string const &cookie) {
    boost::property_tree::ptree ptree;
    ptree.put("cookie", cookie);
    auto client = this->_db->findOne("client", ptree);

    std::string host = client.get<std::string>("host");
    std::string port = client.get<std::string>("port");

    boost::asio::ip::udp::endpoint endpoint = *this->_resolver.resolve({boost::asio::ip::udp::v4(), host, port});

    this->send(data, endpoint);
}

void Server::send(std::string const &data,
                  boost::asio::ip::udp::endpoint &clientEndpoint,
                  std::string const &id) {
    this->sendPacket(data, clientEndpoint, id);
}

void Server::send(std::string const &data,
                  boost::asio::ip::udp::endpoint &clientEndpoint) {
    this->sendPacket(data, clientEndpoint);
}
