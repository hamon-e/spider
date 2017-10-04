#pragma once

#include <unordered_map>
#include <boost/asio.hpp>

#include "Packet.hpp"
#include "IDataBase.hpp"

class PacketManager {
    enum class Error {
        CHECKSUM
    };

public:
    using PacketHandler = std::function<void(Packet &packet)>;
    using ErrorHandler = std::function<void(Packet &packet, PacketManager::Error)>;

public:
    PacketManager(IDataBase &db, PacketHandler handler, ErrorHandler = {});

public:
    PacketManager &in(std::string const &data, boost::asio::ip::udp::endpoint &from);
    // void send(boost::asio::ip::udp::socket &socket, Packet &packet, UdpEndpoint &endpoint);

private:
    // std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Packet>>> _packets;
    PacketHandler _handler;
    ErrorHandler _errorHandler;
    IDataBase &_db;
    // PacketCommunication _com;
};
