<<<<<<< HEAD
//
// main.cpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Wed Oct 04 18:03:49 2017 Benoit Hamon
// Last update Wed Oct 04 20:07:50 2017 Benoit Hamon
//

#include <thread>
#include <boost/asio.hpp>

#include "Client.hpp"
#include "ModuleManager.hpp"

int main(int argc, char const *argv[]) {
  ModuleManager mod;
    boost::asio::io_service ioService;

  mod.run();


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
