#include "LocalDB.hpp"
#include "MongoDB.hpp"
#include "Server.hpp"

Server::Server(boost::asio::io_service &ioService, int port)
    : APacketServer(ioService, port, new MongoDB())
{}

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
      //this->send(this->_crypt.initClient(ptree));
    } else {
      this->_db->update(PacketManager::dataColName, packet.getPtree(), packet.getPtree(), true);
    }
}

void Server::encryptor(Packet &packet) {
  boost::property_tree::ptree ptree;
    boost::property_tree::read_json(packet.get<Packet::Field::DATA, std::string>(), ptree);
  if (ptree.get<std::string>("type") == "AesKey")
    packet.set<std::string>(Packet::Field::DATA,
			    this->_crypt.encryptRSA(packet.get<Packet::Field::COOKIE, std::string>(),
						    packet.get<Packet::Field::DATA, std::string>()));
  else
    packet.set<std::string>(Packet::Field::DATA,
			    this->_crypt.encrypt(packet.get<Packet::Field::COOKIE, std::string>(),
						 packet.get<Packet::Field::DATA, std::string>()));
}

void Server::decryptor(Packet &packet) {
  std::cout << packet.get<Packet::Field::COOKIE, std::string>().empty() << std::endl;
  if (packet.get<Packet::Field::COOKIE, std::string>().empty())
    packet.set<std::string>(Packet::Field::DATA,
			    this->_crypt.decryptRSA(packet.get<Packet::Field::DATA, std::string>()));
  else
    packet.set<std::string>(Packet::Field::DATA,
			    this->_crypt.decrypt(packet.get<Packet::Field::COOKIE, std::string>(),
						 packet.get<Packet::Field::DATA, std::string>()));
}

bool Server::isIgnited(boost::property_tree::ptree const &, boost::asio::ip::udp::endpoint const &) const {
    return true;
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
