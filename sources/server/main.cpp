#include <stdexcept>
#include <boost/asio.hpp>

#include "Server.hpp"

#include <boost/property_tree/ptree.hpp>
#include <sources/MongoDB.hpp>
#include "json.hpp"

namespace pt = boost::property_tree;

int main(int argc, char const *argv[]) {
    MongoDB db;

    if (argc != 2) {
        std::cerr << "Usage : " << argv[0] << " port" << std::endl;
        return 1;
    }

    try {
        boost::asio::io_service ioService;
        Server server(ioService, std::atoi(argv[1]));
        server.start();
        // IntervalService it(ioService, 5, [](boost::system::error_code const &ec) {
        //     std::cout << "azeazeaz" << std::endl;
        // });
        // it.start();
        ioService.run();
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
    return 0;
}
