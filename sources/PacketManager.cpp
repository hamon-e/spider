#include "PacketManager.hpp"
#include "tools.hpp"

std::string const PacketManager::partsColName = "parts";
std::string const PacketManager::dataColName = "data";

PacketManager::PacketManager(IDataBase &db,
                             PacketManager::PacketHandler handler,
                             PacketManager::SuccessHandler successHandler,
                             PacketManager::ErrorHandler errorHandler)
    : _handler(handler), _errorHandler(errorHandler), _succesHandler(successHandler), _db(db)
{}
#include <iostream>

PacketManager &PacketManager::in(std::string const &data, boost::asio::ip::udp::endpoint &from) {
    try {
        Packet packet(data);
        if (!packet.checksum()) {
            std::cout << "err" << std::endl;
            tools::call(this->_errorHandler, packet, PacketManager::Error::CHECKSUM);
        } else {
            this->complete(packet, from);
        }
    } catch (boost::property_tree::json_parser::json_parser_error &err) {
    }
    return *this;
}

void PacketManager::complete(Packet &part, boost::asio::ip::udp::endpoint &from) {
    boost::property_tree::ptree query;
    query.put(Packet::fields.at(Packet::Field::ID), part.get<Packet::Field::ID, std::string>());
    std::vector<boost::property_tree::ptree> packets = this->_db.find(PacketManager::partsColName, query);
    if ((packets.size() + 1) == part.get<Packet::Field::TOTALPART, std::size_t>(0)) {
        std::cout << "ok" << std::endl;
        packets.push_back(std::move(part.getPtree()));
        if (!this->joinParts(packets)) {
            tools::call(this->_succesHandler, part, from);
        }
        try {
            this->_db.remove(PacketManager::partsColName, query);
        } catch (std::exception &) {
        }
    } else {
        std::cout << "nok" << std::endl;
        tools::call(this->_succesHandler, part, from);
    }
    this->_db.insert(PacketManager::partsColName, part.getPtree());
}

 bool PacketManager::joinParts(std::vector<boost::property_tree::ptree> &packets) {
    Packet packet = Packet::join(packets);
    if (packet.getPtree().get("data.type", "") == "success") {
        std::cout << "success" << std::endl;
        return true;
    }
    this->_handler(packet);
    return false;
}
