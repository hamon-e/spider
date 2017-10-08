#include "APacketServer.hpp"

class Server : public APacketServer {
public:
    Server(boost::asio::io_service &ioService, int port);

public:
    void send(std::string const &cookie,
              std::string const &data,
              boost::asio::ip::udp::endpoint &clientEndpoint,
              std::string const &id);
    void send(std::string const &cookie,
              std::string const &data,
              boost::asio::ip::udp::endpoint &clientEndpoint);

private:
    bool requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint);
    void packetHandler(Packet &packet);
};
