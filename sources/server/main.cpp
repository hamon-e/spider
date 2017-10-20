#include <stdexcept>
#include <boost/asio.hpp>

#include "HttpServer.hpp"
#include "Server.hpp"
#include "MongoDB.hpp"

namespace pt = boost::property_tree;

int main(int argc, char const *argv[]) {
  std::string configFile = "config.json";
  if (argc != 2) {
    configFile = argv[1];
    return 1;
  }

  try {
    boost::property_tree::ptree config;
    std::ifstream jsonFile(configFile);

    boost::property_tree::read_json(jsonFile, config);

    boost::asio::io_service ioService;

    MongoDB mongo(config.get("db.host", "localhost"),
                  config.get("db.port", 27017),
                  config.get("db.name", "cpp_spider"));

    Server server(ioService, config.get("port", 1234), &mongo);

    HttpServer httpserver(&mongo, &server, config.get("https.port", 443));

    httpserver.start();
    server.start();

    ioService.run();
    httpserver.join();
  } catch (std::exception &err) {
    std::cout << err.what() << std::endl;
    return 1;
  }
  return 0;
}
