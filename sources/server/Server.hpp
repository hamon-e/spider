#include "AUdpServer.hpp"

class Server : public AUdpServer {
public:
    Server(boost::asio::io_service &io_service, int port);

private:
    void acceptCallback(boost::system::error_code ec, std::string req, boost::asio::ip::udp::endpoint client_endpoint);
};
