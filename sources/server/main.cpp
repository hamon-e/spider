#include <stdexcept>
#include <boost/asio.hpp>

#include "HttpServer.hpp"
#include "Server.hpp"
#include "MongoDB.hpp"

namespace pt = boost::property_tree;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage : " << argv[0] << " port" << std::endl;
        return 1;
    }

    try {
        boost::asio::io_service ioService;

        MongoDB mongo;
        HttpServer httpserver(&mongo, 1234);
        Server server(ioService, std::atoi(argv[1]), &mongo);

        httpserver.start();
        server.start();

        ioService.run();
        httpserver.join();
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
    return 0;
}
