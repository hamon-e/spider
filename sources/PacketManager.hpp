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
    static std::string const waitingColName;

public:
    using PacketHandler = std::function<void(Packet &packet)>;
    using SuccessHandler = std::function<void(Packet &packet, boost::asio::ip::udp::endpoint &from)>;
    using ErrorHandler = std::function<void(Packet &packet, PacketManager::Error)>;

public:
    PacketManager(IDataBase *db, PacketHandler handler, PacketHandler decryptor, SuccessHandler = {}, ErrorHandler = {});

public:
    void setDB(IDataBase *db);

public:
    PacketManager &in(std::string const &data, boost::asio::ip::udp::endpoint &from);

private:
    void complete(boost::property_tree::ptree const &query, boost::asio::ip::udp::endpoint &from, Packet &packet);
    bool joinParts(std::vector<boost::property_tree::ptree> &packets);

private:
    PacketHandler _handler;
    PacketHandler _decryptor;
    ErrorHandler _errorHandler;
    SuccessHandler _succesHandler;
    IDataBase *_db;
};
