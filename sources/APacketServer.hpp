#pragma once

#include <boost/thread/mutex.hpp>

#include "AUdpServer.hpp"
#include "PacketManager.hpp"
#include "IDataBase.hpp"
#include "MapDB.hpp"
#include "IntervalService.hpp"

class APacketServer : public AUdpServer {
  public:
    APacketServer(boost::asio::io_service &ioService, int port, IDataBase *db = nullptr);
    ~APacketServer();

  public:
    void setCookie(std::string const &cookie);
    void sendPacket(
            std::string const &data,
            boost::asio::ip::udp::endpoint const &to,
            std::string const &id,
            bool reserve = true);
    void sendPacket(
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
    virtual void encryptor(Packet &packet, boost::asio::ip::udp::endpoint const &to) = 0;
    virtual std::string encryptorMethod(Packet &packet, boost::asio::ip::udp::endpoint const &to) = 0;
    virtual void decryptor(Packet &packet) = 0;

  protected:
    void saveClient(std::string const &cookie, boost::asio::ip::udp::endpoint const &from);
    void sendSuccess(Packet &packet, boost::asio::ip::udp::endpoint &from);

  protected:
    void setDB(IDataBase *db);

  private:
    void reservePackets(std::vector<Packet> const &packets, boost::asio::ip::udp::endpoint const &to);
    void checkReserve(boost::system::error_code const &ec);

  protected:
    static std::size_t id;

  protected:
    IDataBase *_db;
    std::string _cookie;
    PacketManager _packetManager;
    boost::asio::ip::udp::resolver _resolver;
    IntervalService _reserveChecker;
    boost::mutex _mutex;
};
