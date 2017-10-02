#include "AUdpServer.hpp"

AUdpServer::AUdpServer(boost::asio::io_service &ioService, int port)
    : _socket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
}

void AUdpServer::start() {

    this->_socket.async_receive(
    boost::asio::null_buffers(),
    // boost::asio::buffer(this->c),
    // this->_clientEndpoint,
    [this](boost::system::error_code, std::size_t size) {
        boost::system::error_code ec;
        size_t available = this->_socket.available();
        std::string req;
        req.resize(available + 1);
        this->_socket.receive_from(boost::asio::buffer(&(req[0]), req.size()), this->_clientEndpoint, 0, ec);
        std::cout << "req :" << req << std::endl;
        if (ec) {
            std::cout << "err : " << ec << std::endl;
        }
        this->acceptCallback(ec, std::move(req), std::move(this->_clientEndpoint));
        this->start();
    });
}
