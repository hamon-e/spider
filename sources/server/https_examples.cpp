#include "SimpleWebServer/client_https.hpp"
#include "SimpleWebServer/server_https.hpp"

// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include "SimpleWebServer/crypto.hpp"
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;

int main() {
  HttpsServer server("server.crt", "server.key");
  server.config.port = 8080;

  server.resource["^/json$"]["POST"] = [](shared_ptr<HttpsServer::Response> response, shared_ptr<HttpsServer::Request> request) {
    try {
      ptree pt;
      read_json(request->content, pt);

      auto name = pt.get<string>("firstName") + " " + pt.get<string>("lastName");

      *response << "HTTP/1.1 200 OK\r\n"
                << "Content-Length: " << name.length() << "\r\n\r\n"
                << name;
    }
    catch(const exception &e) {
      *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
                << e.what();
    }


    // Alternatively, using a convenience function:
    // try {
    //     ptree pt;
    //     read_json(request->content, pt);

    //     auto name=pt.get<string>("firstName")+" "+pt.get<string>("lastName");
    //     response->write(name);
    // }
    // catch(const exception &e) {
    //     response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    // }
  };

  server.on_error = [](shared_ptr<HttpsServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
    // Handle errors here
  };

  boost::thread server_thread([&server]() {server.start();});

  server_thread.join();
}
