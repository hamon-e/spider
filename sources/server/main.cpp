#include <boost/asio.hpp>

#include "Server.hpp"

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        std::cerr << "Usage : " << argv[0] << " port" << std::endl;
        return 1;
    }

    boost::asio::io_service ioService;
    Server server(ioService, std::atoi(argv[1]));
    server.start();
    ioService.run();
    return 0;
}
