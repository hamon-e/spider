#include "UdpEndpoint.hpp"

UdpEndpoint::UdpEndpoint(boost::asio::io_service &ioService, std::string const &host, std::string const &port) {
  boost::asio::ip::udp::resolver resolver(ioService);
  this->_endpoint = *resolver.resolve({boost::asio::ip::udp::v4(), host, port});
}

UdpEndpoint::UdpEndpoint(boost::asio::ip::udp::endpoint &endpoint)
        : _endpoint(endpoint)
{}

UdpEndpoint::UdpEndpoint(boost::asio::ip::udp::endpoint &&endpoint)
        : _endpoint(std::move(endpoint))
{}

bool UdpEndpoint::operator!=(boost::asio::ip::udp::endpoint const &endpoint) const {
  return this->_endpoint != endpoint;
}


void UdpEndpoint::send(boost::asio::ip::udp::socket &socket, std::string const &msg) const {
  socket.send_to(boost::asio::buffer(msg, msg.length()), this->_endpoint);
};

std::string UdpEndpoint::receive(boost::asio::ip::udp::socket &socket) const {
  std::string message;
  message.resize(socket.available());
  socket.receive(boost::asio::buffer(&(message[0]), message.size()));
  return message;
}
