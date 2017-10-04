#pragma once

#include "APacketServer.hpp"
#include "../UdpEndpoint.hpp"

class Client : public APacketServer {
public:
    Client(boost::asio::io_service &ioService, std::string const &host, std::string const &port);

public:
    void send(std::string const &msg);

private:
    virtual bool requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &client_endpoint);
    virtual void packetHandler(Packet &packet);

private:
    UdpEndpoint _serverEndpoint;
};
