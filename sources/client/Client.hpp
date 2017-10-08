#pragma once

#include "APacketServer.hpp"
#include "IModuleCommunication.hpp"
#include "ModuleManager.hpp"

class Client : public APacketServer {
public:
    Client(boost::asio::io_service &ioService, std::string const &host, std::string const &port);

public:
    void send(std::string const &cookie,
              std::string const &type,
              std::string const &data,
              std::string const &id);
    void send(std::string const &cookie,
              std::string const &type,
              std::string const &data);

public:
    void addModuleCommunication(IModuleCommunication *moduleCommunication);

private:
    static std::size_t id;

private:
    virtual bool requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint);
    virtual void packetHandler(Packet &packet);

private:
    boost::asio::ip::udp::endpoint _serverEndpoint;
    IModuleCommunication *_moduleCommunication;
    ModuleManager _moduleManager;
};
