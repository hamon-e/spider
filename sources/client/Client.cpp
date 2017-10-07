#include "Client.hpp"

std::size_t Client::id = 0;

Client::Client(boost::asio::io_service &ioService, std::string const &host, std::string const &port)
    : APacketServer(ioService, 0)
{
    boost::asio::ip::udp::resolver resolver(ioService);
    this->_serverEndpoint = *resolver.resolve({boost::asio::ip::udp::v4(), host, port});
}

bool Client::requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint) {
    if (this->_serverEndpoint != clientEndpoint) {
        return false;
    }
    return true;
}

void Client::packetHandler(Packet &packet) {
}

void Client::send(std::string const &cookie,
                  std::string const &data,
                  std::string const &id) {
    this->sendPacket(id, cookie, data, this->_serverEndpoint);
}
void Client::send(std::string const &cookie,
                  std::string const &data) {
    std::cout << Client::id << std::endl;
    this->send(cookie, data, std::to_string(Client::id++));
}
