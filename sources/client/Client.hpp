#pragma once

#include "APacketServer.hpp"
#include "CryptClient.hpp"
#include "IModuleCommunication.hpp"
#include "ModuleManager.hpp"

class Client : public APacketServer {
public:
    Client(boost::asio::io_service &ioService, std::string const &cookie, std::string const &host, std::string const &port);

public:
    void send(std::string const &data,
              std::string const &id,
              std::size_t size = Packet::defaultSize,
              bool force = false);
    void send(std::string const &data, std::size_t size = Packet::defaultSize, bool force = false);
    void run();

public:
    void addModuleCommunication(IModuleCommunication *moduleCommunication);

private:
    virtual bool requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint);
    virtual void packetHandler(Packet &packet);
    virtual void encryptor(Packet &packet);
    virtual void decryptor(Packet &packet);
    virtual bool isIgnited(boost::property_tree::ptree const &packet, boost::asio::ip::udp::endpoint const &clientEndpoint) const;

private:
    boost::asio::ip::udp::endpoint _serverEndpoint;
    CryptClient _crypt;
    IModuleCommunication *_moduleCommunication;
    ModuleManager _moduleManager;
};
