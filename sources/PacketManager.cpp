#include "PacketManager.hpp"

std::string const PacketManager::partsColName = "parts";
std::string const PacketManager::dataColName = "data";

PacketManager::PacketManager(IDataBase &db,
                             PacketManager::PacketHandler handler,
                             PacketManager::ErrorHandler errorHandler)
    : _handler(handler), _errorHandler(errorHandler), _db(db)
{}

PacketManager &PacketManager::in(std::string const &data, boost::asio::ip::udp::endpoint &from) {
    Packet packet(data);
    if (!packet.checksum()) {
        if (this->_errorHandler) {
            this->_errorHandler(packet, PacketManager::Error::CHECKSUM);
        }
    } else {
        this->complete(packet);
    }
    return *this;
}

void PacketManager::complete(Packet &part) {
    boost::property_tree::ptree query;
    query.put(Packet::fields.at(Packet::Field::ID), part.get<Packet::Field::ID, std::string>());
    std::vector<boost::property_tree::ptree> packets = this->_db.find(PacketManager::partsColName, query);
    if ((packets.size() + 1) == part.get<Packet::Field::TOTALPART, std::size_t>(0)) {
        packets.push_back(std::move(part.getPtree()));
        this->joinParts(packets);
        try {
            this->_db.remove(PacketManager::partsColName, query);
        } catch (std::exception &) {
        }
    } else {
        this->_db.insert(PacketManager::partsColName, part.getPtree());
    }
}

void PacketManager::joinParts(std::vector<boost::property_tree::ptree> &packets) {
    Packet packet = Packet::join(packets);
    this->_handler(packet);
}
