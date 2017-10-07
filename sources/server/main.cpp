#include <boost/asio.hpp>

#include "Server.hpp"

#include <boost/property_tree/ptree.hpp>
#include <sources/MongoDB.hpp>
#include "json.hpp"

namespace pt = boost::property_tree;

int main(int argc, char const *argv[]) {
/*
    MongoDB db;
    pt::ptree tree;

    tree.put("id", 1);
    tree.put("timestamp", 239);
    tree.put("part", 2);
    tree.put("checksum", 6);
    tree.put("data.key", "oiergoerihgerio");
    tree.put("data.process", "discord");

    db.insert("parts", tree);
*/

    if (argc != 2) {
        std::cerr << "Usage : " << argv[0] << " port" << std::endl;
        return 1;
    }

    boost::asio::io_service ioService;
    Server server(ioService, std::atoi(argv[1]));
    server.start();
    ioService.run();
    return 0;
}
