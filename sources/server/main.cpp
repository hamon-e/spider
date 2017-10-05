#include <boost/asio.hpp>

#include "Server.hpp"

#include <boost/property_tree/ptree.hpp>
#include "json.hpp"

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        std::cerr << "Usage : " << argv[0] << " port" << std::endl;
        return 1;
    }


    // boost::property_tree::ptree ptree;
    // std::stringstream ss;
    // std::cout << "{\"id\":\"0\",\"timestamp\":\"0\",\"part\":\"1\",\"total\":\"1\",\"data\":\"hello\",\"checksum\":\"2762169579135187400\"}" << std::endl;
    // std::cout << data << std::endl;
    // boost::property_tree::json_parser::read_json(ss, ptree);

    boost::asio::io_service ioService;
    Server server(ioService, std::atoi(argv[1]));
    server.start();
    ioService.run();
    return 0;
}
