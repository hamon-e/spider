#include "PacketManager.hpp"

PacketManager::PacketManager(IDataBase &db,
                             PacketManager::PacketHandler handler,
                             PacketManager::ErrorHandler errorHandler)
    : _handler(handler), _errorHandler(errorHandler), _db(db)
{}

PacketManager &PacketManager::in(std::string const &data, boost::asio::ip::udp::endpoint &from) {
    Packet packet(data);
    if (packet.checksum()) {
        this->_errorHandler(packet, PacketManager::Error::CHECKSUM);
    } else {
        Packet::partPair part = packet.getPartPair();
        this->_handler(packet);
    }
    return *this;
}
