#pragma once

#include "AUdpServer.hpp"
#include "PacketManager.hpp"
#include "IDataBase.hpp"
#include "MapDB.hpp"

class APacketServer : public AUdpServer {
public:
    APacketServer(boost::asio::io_service &ioService, int port, IDataBase *db = new MapDB());

public:
    void sendPacket(
        std::string const &id,
        std::string const &cookie,
        std::string const &type,
        std::string const &timestamp,
        std::string const &data,
        boost::asio::ip::udp::endpoint &to
        );

private:
    void requestHandler(boost::system::error_code ec,
                        std::string req,
                        boost::asio::ip::udp::endpoint clientEndpoint);

    virtual bool requestCheck(boost::system::error_code &ec,
                              std::string &req,
                              boost::asio::ip::udp::endpoint &clientEndpoint) = 0;
    virtual void packetHandler(Packet &packet) = 0;


protected:
    IDataBase *_db;
    PacketManager _packetManager;
};
