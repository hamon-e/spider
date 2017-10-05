#pragma once

#include <unordered_map>
#include <boost/asio.hpp>

#include "Packet.hpp"
#include "IDataBase.hpp"

class PacketManager {
public:
    enum class Error {
        CHECKSUM
    };

    static std::string const partsColName;
    static std::string const dataColName;

public:
    using PacketHandler = std::function<void(Packet &packet)>;
    using ErrorHandler = std::function<void(Packet &packet, PacketManager::Error)>;

public:
    PacketManager(IDataBase &db, PacketHandler handler, ErrorHandler = {});

public:
    PacketManager &in(std::string const &data, boost::asio::ip::udp::endpoint &from);

private:
    void complete(Packet &packet);
    void joinParts(std::vector<boost::property_tree::ptree> &packets);
private:
    PacketHandler _handler;
    ErrorHandler _errorHandler;
    IDataBase &_db;
};
