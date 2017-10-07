//
// main.cpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Wed Oct 04 18:03:49 2017 Benoit Hamon
// Last update Sat Oct 07 23:24:51 2017 Benoit Hamon
//

#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "Client.hpp"
#include "ModuleCommunication.hpp"
#include "ModuleManager.hpp"

int main(int argc, char const *argv[]) {
    boost::asio::io_service ioService;

    if (argc < 3) {
        return 1;
    }


    Client client(ioService, argv[1], argv[2]);
    ModuleCommunication moduleCommunication(client);
    client.start();

    boost::thread modules([&moduleCommunication]() {
	ModuleManager mod(&moduleCommunication);
	mod.run();
	});

    ioService.run();
    modules.join();
    return 0;
}
