#include "Server.hpp"

Server::Server(boost::asio::io_service &ioService, int port)
    : AUdpServer(ioService, port)
{
}

void Server::acceptCallback(boost::system::error_code ec,
                            std::string req,
                            boost::asio::ip::udp::endpoint clientEndpoint) {
    auto message = std::make_shared<std::string>("> Hello, World !\n");
    std::cout << "at :" << clientEndpoint << std::endl;
    _socket.async_send_to(
    boost::asio::buffer(*message),
    clientEndpoint,
    [this, message](boost::system::error_code const &ec, std::size_t) {
        std::cout << "sent" << std::endl;
    });
}
