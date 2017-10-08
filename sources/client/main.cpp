#include <stdexcept>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "Client.hpp"
#include "ModuleManager.hpp"

int main(int argc, char const *argv[]) {
    boost::asio::io_service ioService;

    if (argc < 3) {
        return 1;
    }

    // try {
        Client client(ioService, argv[1], argv[2]);
        client.send("Nicolas", "{ \"aze\": \"helloazeazeazeazeazeazeaz\" }");
        client.start();
        boost::thread([&client]() {
            std::string s;
            while (getline(std::cin, s)) {
                client.send("aze", "{\"aze\": \"" + s + "\" }");
            }
        });
        // boost::thread modules([&client]() {
    	// ModuleManager mod(client);
    	// mod.run();
    	// });

        ioService.run();
        // modules.join();
    // } catch(std::exception &err) {
    //     std::cout << err.what() << std::endl;
    //     return 1;
    // }
    return 0;
}
