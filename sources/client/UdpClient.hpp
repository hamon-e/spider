#include <boost/asio.hpp>
#include <iostream>

class UdpClient {
public:
    UdpClient(boost::asio::io_service &ioService, std::string const &host, std::string const &port);

    void send(std::string const &msg);

    std::string receive();

private:
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _endpoint;
};
