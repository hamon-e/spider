#pragma once

#include <boost/asio.hpp>
#include <iostream>

class AUdpServer {
public:
    AUdpServer(boost::asio::io_service &io_service, int port);

public:
    bool start();
    bool isStarted() const;

private:
    void listen();
    virtual void requestHandler(boost::system::error_code ec,
                                std::string req,
                                boost::asio::ip::udp::endpoint client_endpoint) = 0;

protected:
    bool started;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _clientEndpoint;
};
