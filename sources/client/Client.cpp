#include "Client.hpp"

Client::Client(boost::asio::io_service &ioService, std::string const &host, std::string const &port)
    : APacketServer(ioService, 0), _serverEndpoint(ioService, host, port)
{}

bool Client::requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint) {
    if (this->_serverEndpoint != clientEndpoint) {
        return false;
    }
    return true;
}

void Client::packetHandler(Packet &packet) {
}

void Client::send(std::string const &msg) {
    this->_serverEndpoint.send(this->_socket, msg);
};
