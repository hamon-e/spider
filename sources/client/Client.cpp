#include <LocalDB.hpp>
#include "Client.hpp"

Client::Client(boost::asio::io_service &ioService, std::string const &cookie, std::string const &host, std::string const &port)
    : APacketServer(ioService, 0, cookie, new LocalDB())
{
    this->_serverEndpoint = *this->_resolver.resolve({boost::asio::ip::udp::v4(), host, port});
    this->saveClient("SERVER", this->_serverEndpoint);
    this->_isIgnited = false;
}

void Client::run() {
  this->_moduleManager.run();
}

void Client::addModuleCommunication(IModuleCommunication *moduleCommunication) {
  this->_moduleCommunication = moduleCommunication;
  this->_moduleManager.addModuleCommunication(moduleCommunication);
  this->_crypt.addModuleCommunication(moduleCommunication);
  this->_crypt.init();
}

bool Client::requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint) {
    if (this->_serverEndpoint != clientEndpoint) {
        return false;
    }
    return true;
}

void Client::packetHandler(Packet &packet) {
  auto data = packet.get<Packet::Field::DATA, std::string>();
  boost::property_tree::ptree ptree;

  boost::property_tree::read_json(data, ptree);
  if (ptree.get<std::string>("type") == "Order") {
    this->_moduleCommunication->add(ptree.get_child("order"));
  } else if (ptree.get<std::string>("type") == "Upload")
    this->_moduleManager.addLibrary(ptree.get_child("lib"));
  else if (ptree.get<std::string>("type") == "Key") {
    this->_crypt.init(ptree.get_child("key"));
    this->_isIgnited = true;
  }
}

void Client::encryptor(Packet &packet) {
  std::cout << this->_crypt.encrypt(packet.get<Packet::Field::DATA, std::string>()) << std::endl;
  packet.set<std::string>(Packet::Field::DATA,
			  this->_crypt.encrypt(packet.get<Packet::Field::DATA, std::string>()));
}

void Client::decryptor(Packet &packet) {
  packet.set<std::string>(Packet::Field::DATA,
			  this->_crypt.decrypt(packet.get<Packet::Field::DATA, std::string>()));
}

bool Client::isIgnited(boost::property_tree::ptree const &packet,
		       boost::asio::ip::udp::endpoint const &clientEndpoint) const {
  return this->_isIgnited;
}

void Client::send(std::string const &data,
                  std::string const &id,
                  bool force) {
    this->sendPacket(data, this->_serverEndpoint, id);
}

void Client::send(std::string const &data, bool force) {
    this->sendPacket(data, this->_serverEndpoint);
}
