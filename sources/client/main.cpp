#include <thread>
#include <boost/asio.hpp>

#include "Client.hpp"

int main(int argc, char const *argv[]) {
    boost::asio::io_service ioService;

    if (argc < 3) {
        return 1;
    }

    Client client(ioService, argv[1], argv[2]);
    client.send("Nicolas", "plain_text", "helloazeazeazeazeazeazeaz");
    client.start();
    std::thread input([&client]() {
        std::string line;
        while (getline(std::cin, line)) {
            client.send("Nicolas", "caca", line);
        }
    });
    ioService.run();
    input.join();
    return 0;
}
