#include "APacketServer.hpp"

class Server : public APacketServer {
public:
    Server(boost::asio::io_service &ioService, int port);

private:
    bool requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &client_endpoint);
    void packetHandler(Packet &packet);
};
