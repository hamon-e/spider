#include <stdexcept>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <LocalDB.hpp>

#include "Client.hpp"
#include "ModuleManager.hpp"

namespace pt = boost::property_tree;

int main(int argc, char const *argv[]) {
    boost::asio::io_service ioService;

    if (argc < 3) {
        return 1;
    }

    try {
        Client client(ioService, "Nicolas", argv[1], argv[2]);
        client.send("{ \"aze\": \"helloazeazeazeazeazeazeaz\" }");
        client.start();
        boost::thread modules([&client]() {
    	ModuleManager mod(client);
    	mod.run();
    	});

        ioService.run();
        modules.join();
    } catch(std::exception &err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
    return 0;
}
