#include "LocalDB.hpp"
#include "MongoDB.hpp"
#include "Server.hpp"

Server::Server(boost::asio::io_service &ioService, int port)
    : APacketServer(ioService, port, "SERVER", new MongoDB())
{}

bool Server::requestCheck(boost::system::error_code &,
                            std::string &,
                            boost::asio::ip::udp::endpoint &) {
    return true;
}

void Server::packetHandler(Packet &packet) {
    std::cout << "completed " << packet << std::endl;
    this->_db->update(PacketManager::dataColName, packet.getPtree(), packet.getPtree(), true);
}

void Server::send(std::string const &data,
                  boost::asio::ip::udp::endpoint &clientEndpoint,
                  std::string const &id) {
    this->sendPacket(data, clientEndpoint, id);
}

void Server::send(std::string const &data,
                  boost::asio::ip::udp::endpoint &clientEndpoint) {
    this->sendPacket(data, clientEndpoint);
}
