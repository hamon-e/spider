#include "APacketServer.hpp"
#include "MapDB.hpp"

APacketServer::APacketServer(boost::asio::io_service &ioService, int port)
    : AUdpServer(ioService, port),
      _packetManager(
        this->_db,
        [this](Packet &packet) { this->packetHandler(packet); }
      )
{}

void APacketServer::sendPacket(std::string const &id,
                               std::string const &cookie,
                               std::string const &type,
                               std::string const &timestamp,
                               std::string const &data,
                               boost::asio::ip::udp::endpoint &to) {
    Packet packet;
    packet.set(Packet::Field::ID, id);
    packet.set(Packet::Field::COOKIE, cookie);
    packet.set(Packet::Field::TYPE, type);
    packet.set(Packet::Field::TIMESTAMP, timestamp);
    packet.set(Packet::Field::DATA, data);
    for (auto part : packet.split()) {
        std::string msg(std::move(part.stringify()));
        this->_socket.send_to(boost::asio::buffer(msg, msg.length()), to);
    }
}

void APacketServer::requestHandler(boost::system::error_code ec,
                                   std::string req,
                                   boost::asio::ip::udp::endpoint clientEndpoint) {
    std::size_t index = req.find_last_not_of("\n\r");
    req.resize(index);
    if (this->requestCheck(ec, req, clientEndpoint)) {
        this->_packetManager.in(req, clientEndpoint);
    }
}
