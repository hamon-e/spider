#include <LocalDB.hpp>
#include "Client.hpp"

Client::Client(boost::asio::io_service &ioService, std::string const &cookie, std::string const &host, std::string const &port)
    : APacketServer(ioService, 0, cookie, new LocalDB())
{
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
  else if (ptree.get<std::string>("type") == "Key")
    this->_crypt.init(ptree.get_child("key"));
}

void Client::send(std::string const &data,
                  std::string const &id) {
    this->sendPacket(data, this->_serverEndpoint, id);
}

void Client::send(std::string const &data) {
    this->sendPacket(data, this->_serverEndpoint);
}
