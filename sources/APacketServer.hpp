#pragma once

#include "AUdpServer.hpp"
#include "PacketManager.hpp"
#include "IDataBase.hpp"
#include "MapDB.hpp"
#include "IntervalService.hpp"

class APacketServer : public AUdpServer {
public:
    APacketServer(boost::asio::io_service &ioService, int port, IDataBase *db = new MapDB());
    ~APacketServer();

public:
    void sendPacket(
        std::string const &cookie,
        std::string const &data,
        boost::asio::ip::udp::endpoint const &to,
        std::string const &id,
        bool reserve = true);
        void sendPacket(
            std::string const &cookie,
            std::string const &data,
            boost::asio::ip::udp::endpoint &to,
            bool reserve = true);

private:
    void requestHandler(boost::system::error_code ec,
                        std::string req,
                        boost::asio::ip::udp::endpoint clientEndpoint);

    virtual bool requestCheck(boost::system::error_code &ec,
                              std::string &req,
                              boost::asio::ip::udp::endpoint &clientEndpoint) = 0;
    virtual void packetHandler(Packet &packet) = 0;

protected:
    void saveClient(std::string const &cookie, boost::asio::ip::udp::endpoint const &from);
    void sendSuccess(Packet &packet, boost::asio::ip::udp::endpoint &from);

private:
    void reservePackets(std::vector<Packet> const &packets, boost::asio::ip::udp::endpoint const &to);
    void checkReserve(boost::system::error_code const &ec);

protected:
    static std::size_t id;

protected:
    IDataBase *_db;
    PacketManager _packetManager;
    boost::asio::ip::udp::resolver _resolver;
    IntervalService _reserveChecker;
};
