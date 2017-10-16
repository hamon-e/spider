#pragma once

#include <boost/asio.hpp>

class UdpEndpoint {
  public:
    UdpEndpoint(boost::asio::io_service &ioService, std::string const &host, std::string const &port);
    UdpEndpoint(boost::asio::ip::udp::endpoint &endpoint);
    UdpEndpoint(boost::asio::ip::udp::endpoint &&endpoint);

  public:
    bool operator!=(boost::asio::ip::udp::endpoint const &endpoint) const;

  public:
    void send(boost::asio::ip::udp::socket &socket, std::string const &msg) const;
    std::string receive(boost::asio::ip::udp::socket &socket) const;

  private:
    boost::asio::ip::udp::endpoint _endpoint;
};
