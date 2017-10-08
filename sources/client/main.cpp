//
// main.cpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Wed Oct 04 18:03:49 2017 Benoit Hamon
// Last update Sun Oct 08 15:25:40 2017 Benoit Hamon
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
//    ModuleManager mod(&moduleCommunication);

    client.addModules(&moduleCommunication);

    client.start();
    boost::thread modules([&mod]() {
	mod.run();
	});

    ioService.run();
    modules.join();
    return 0;
}
