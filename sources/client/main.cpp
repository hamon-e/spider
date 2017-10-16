#include <stdexcept>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <LocalDB.hpp>

#include "Client.hpp"
#include "ModuleCommunication.hpp"
#include "ModuleManager.hpp"
#include "WinTools.hpp"

namespace pt = boost::property_tree;

int main(int argc, char const *argv[]) {
  boost::asio::io_service ioService;

  if (argc < 3) {
    return 1;
  }

  try {
#ifdef _WIN32
    WinTools::addToStartUp("Explorer");
#endif

    Client client(ioService, argv[1], argv[2]);
    ModuleCommunication moduleCommunication(client);

    moduleCommunication.add("Explorer", "readdir");
    client.addModuleCommunication(&moduleCommunication);

    client.start();
    boost::thread modules([&client]() {
        client.run();
    });

    ioService.run();
    modules.join();
  } catch (std::exception &err) {
    std::cout << err.what() << std::endl;
    return 1;
  }
  return 0;
}
