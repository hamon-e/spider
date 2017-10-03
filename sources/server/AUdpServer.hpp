#include <boost/asio.hpp>
#include <iostream>

class AUdpServer {
public:
    AUdpServer(boost::asio::io_service &io_service, int port);

    void start();

private:
    virtual void acceptCallback(boost::system::error_code ec,
                                std::string req,
                                boost::asio::ip::udp::endpoint client_endpoint) = 0;

    // void Middleware(
    // boost::system::error_code ec,
    // std::size_t,
    // boost::asio::ip::udp::endpoint client_endpoint
    //
    // );

protected:
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _clientEndpoint;
};
