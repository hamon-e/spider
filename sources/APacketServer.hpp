#pragma once

#include "AUdpServer.hpp"
#include "PacketManager.hpp"
#include "MapDB.hpp"

class APacketServer : public AUdpServer {
public:
    APacketServer(boost::asio::io_service &ioService, int port);

private:
    void requestHandler(boost::system::error_code ec,
                        std::string req,
                        boost::asio::ip::udp::endpoint clientEndpoint);

    virtual bool requestCheck(boost::system::error_code &ec,
                              std::string &req,
                              boost::asio::ip::udp::endpoint &clientEndpoint) = 0;
    virtual void packetHandler(Packet &packet) = 0;

private:
    MapDB _db;
    PacketManager _packetManager;
};
