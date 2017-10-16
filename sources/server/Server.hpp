#pragma once

#include "APacketServer.hpp"
#include "CryptServer.hpp"

class Server : public APacketServer {
  public:
    Server(boost::asio::io_service &ioService, int port, IDataBase *db);

  public:
    void send(std::string const &data,
              boost::asio::ip::udp::endpoint &clientEndpoint,
              std::string const &id);
    void send(std::string const &data,
              boost::asio::ip::udp::endpoint &clientEndpoint);
    void send(std::string const &data,
              std::string const &cookie);

  private:
    bool requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint);
    void packetHandler(Packet &packet);
    virtual void encryptor(Packet &packet, boost::asio::ip::udp::endpoint const &to);
    virtual std::string encryptorMethod(Packet &packet, boost::asio::ip::udp::endpoint const &to);
    virtual void decryptor(Packet &packet);

  private:
    CryptServer _crypt;
};
