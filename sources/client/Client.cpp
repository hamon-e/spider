#include <LocalDB.hpp>
#include "Client.hpp"

Client::Client(boost::asio::io_service &ioService, std::string const &cookie, std::string const &host, std::string const &port)
    : APacketServer(ioService, 0, cookie, new LocalDB())
{
    this->_serverEndpoint = *this->_resolver.resolve({boost::asio::ip::udp::v4(), host, port});
    this->saveClient("SERVER", this->_serverEndpoint);
}

bool Client::requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint) {
    if (this->_serverEndpoint != clientEndpoint) {
        return false;
    }
    return true;
}

void Client::packetHandler(Packet &packet) {
    std::cout << "completed " << packet << std::endl;
}

void Client::send(std::string const &data,
                  std::string const &id) {
    this->sendPacket(data, this->_serverEndpoint, id);
}

void Client::send(std::string const &data) {
    this->sendPacket(data, this->_serverEndpoint);
}
