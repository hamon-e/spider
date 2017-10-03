#include "UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_service &ioService, std::string const &host, std::string const &port)
    : _socket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0))
{
    boost::asio::ip::udp::resolver resolver(ioService);
    this->_endpoint = *resolver.resolve({boost::asio::ip::udp::v4(), host, port});
}

void UdpClient::send(std::string const &msg) {
    this->_socket.send_to(boost::asio::buffer(msg, msg.length()), this->_endpoint);
};

std::string UdpClient::receive() {
    std::string message;
    message.resize(this->_socket.available());
    this->_socket.receive(boost::asio::buffer(&(message[0]), message.size()));
    return message;
}
