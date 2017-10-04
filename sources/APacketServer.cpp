#include "APacketServer.hpp"
#include "MapDB.hpp"

APacketServer::APacketServer(boost::asio::io_service &ioService, int port)
    : AUdpServer(ioService, port),
      _packetManager(
        this->_db,
        [this](Packet &packet) { this->packetHandler(packet); }
      )
{}

void APacketServer::requestHandler(boost::system::error_code ec,
                             std::string req,
                             boost::asio::ip::udp::endpoint clientEndpoint) {
    if (this->requestCheck(ec, req, clientEndpoint)) {
        this->_packetManager.in(req, clientEndpoint);
    }
}
