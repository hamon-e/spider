#include "PacketManager.hpp"
#include "tools.hpp"

std::string const PacketManager::partsColName = "parts";
std::string const PacketManager::dataColName = "data";
std::string const PacketManager::waitingColName = "waiting";

PacketManager::PacketManager(IDataBase *db,
                             PacketManager::PacketHandler handler,
                             PacketManager::SuccessHandler successHandler,
                             PacketManager::ErrorHandler errorHandler)
    : _handler(handler), _errorHandler(errorHandler), _succesHandler(successHandler), _db(db)
{}

void PacketManager::setDB(IDataBase *db) {
    this->_db = db;
}

PacketManager &PacketManager::in(std::string const &data, boost::asio::ip::udp::endpoint &from) {
    try {
        Packet packet(data);
        if (!packet.checksum()) {
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

    std::vector<boost::property_tree::ptree> packets = this->_db->find(PacketManager::partsColName, query);
    if ((packets.size() + 1) == part.get<Packet::Field::TOTALPART, std::size_t>(0)) {
        packets.push_back(std::move(part.getPtree()));
        if (!this->joinParts(packets)) {
            tools::call(this->_succesHandler, part, from);
        }
        try {
            this->_db->remove(PacketManager::partsColName, query);
        } catch (std::exception &) {
        }
    } else {
        tools::call(this->_succesHandler, part, from);
    }

    query.put(Packet::fields.at(Packet::Field::PART), part.get<Packet::Field::PART, std::string>());
    this->_db->update(PacketManager::partsColName, part.getPtree(), part.getPtree(), true);
}

 bool PacketManager::joinParts(std::vector<boost::property_tree::ptree> &packets) {
    Packet packet = Packet::join(packets);
    boost::property_tree::ptree query;
    try {
        auto ptree = packet.getPtree();
        if (ptree.get("data.type", "") == "success") {
            query.put("packet.id", ptree.get("data.id", ""));
            query.put("packet.part", ptree.get("data.part", ""));
            try {
                this->_db->remove(PacketManager::waitingColName, query);
            } catch (std::exception &err) {
            }
            return true;
        }
    } catch (std::exception &) {
    }
    this->_handler(packet);
    return false;
}
