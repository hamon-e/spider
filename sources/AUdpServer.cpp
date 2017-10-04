#include "AUdpServer.hpp"

AUdpServer::AUdpServer(boost::asio::io_service &ioService, int port)
    : started(false), _socket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
}

bool AUdpServer::isStarted() const {
    return this->started;
}

bool AUdpServer::start() {
    if (this->isStarted()) {
        return false;
    }
    this->started = true;
    this->listen();
    return true;
}

void AUdpServer::listen() {
    if (!this->isStarted()) {
        return;
    }
    this->_socket.async_receive(
        boost::asio::null_buffers(),
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
            this->requestHandler(ec, std::move(req), std::move(this->_clientEndpoint));
            this->listen();
        }
    );
}
