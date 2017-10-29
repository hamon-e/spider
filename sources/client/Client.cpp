#include <LocalDB.hpp>
#include "Client.hpp"

Client::Client(boost::asio::io_service &ioService, std::string const &host, std::string const &port)
        : APacketServer(ioService, 0, new LocalDB()) {
  this->_serverEndpoint = *this->_resolver.resolve({boost::asio::ip::udp::v4(), host, port});
  this->saveClient("SERVER", this->_serverEndpoint);
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
  std::cout << packet << std::endl;
  auto data = packet.get<Packet::Field::DATA, std::string>();
  boost::property_tree::ptree ptree = packet.getPtree();

  if (ptree.get<std::string>("data.type") == "Order") {
    this->_moduleCommunication->add(ptree.get_child("data.order"));
  } else if (ptree.get<std::string>("data.type") == "Upload")
    this->_moduleManager.addLibrary(ptree.get_child("data.lib"));
  else if (ptree.get<std::string>("data.type") == "AesKey") {
    this->_crypt.init(ptree.get<std::string>("data.key.AES_KEY"),
                      ptree.get<std::string>("data.key.AES_IV"));
    this->_cookie = ptree.get<std::string>("data.key.cookie");
  }
}

void Client::encryptor(Packet &packet, boost::asio::ip::udp::endpoint const &) {
  this->_crypt.encrypt(packet);
}

std::string Client::encryptorMethod(Packet &packet, boost::asio::ip::udp::endpoint const &) {
  return this->_crypt.encryptMethod(packet);
}

void Client::decryptor(Packet &packet) {
  this->_crypt.decrypt(packet);
}

void Client::send(std::string const &data,
                  std::string const &id) {
  this->sendPacket(data, this->_serverEndpoint, id);
}

void Client::send(std::string const &data) {
  this->sendPacket(data, this->_serverEndpoint);
}
