#include "Client.hpp"

std::size_t Client::id = 0;

Client::Client(boost::asio::io_service &ioService, std::string const &host, std::string const &port)
    : APacketServer(ioService, 0) {
    boost::asio::ip::udp::resolver resolver(ioService);
    this->_serverEndpoint = *resolver.resolve({boost::asio::ip::udp::v4(), host, port});
}

void Client::run() {
  this->_moduleManager.run();
}

void Client::addModuleCommunication(IModuleCommunication *moduleCommunication) {
  this->_moduleCommunication = moduleCommunication;
  this->_moduleManager.addModuleCommunication(moduleCommunication);
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
}

void Client::send(std::string const &cookie,
                  std::string const &type,
                  std::string const &data,
                  std::string const &id) {
    this->sendPacket(id, cookie, type, data, this->_serverEndpoint);
}

void Client::send(std::string const &cookie,
                  std::string const &type,
                  std::string const &data) {
    std::cout << Client::id << std::endl;
    this->send(cookie, type, data, std::to_string(Client::id++));
}

// void Client::send(std::string const &msg) {
//     this->_serverEndpoint.send(this->_socket, msg);
// };
