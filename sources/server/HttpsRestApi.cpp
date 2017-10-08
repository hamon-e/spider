//
// HttpsRestApi.cpp for cpp_spider in sources/server
//
// Made by Nicolas Goudal
// Login   <nicolas.goudal@epitech.eu>
//
// Started on  Sun Oct 08 18:38:49 2017 Nicolas Goudal
// Last update Sun Oct 08 20:41:42 2017 Benoit Hamon
//

#include "SimpleWebServer/client_https.hpp"
#include "SimpleWebServer/server_https.hpp"
#include "SimpleWebServer/crypto.hpp"

#include <vector>
#include <fstream>
#include <algorithm>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

#include "MongoDB.hpp"

using namespace std;
using namespace boost::property_tree;

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;

std::string GenCookie() {
  const int length = 32;
  auto randchar = []() -> char {
    const char charset[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[rand() % max_index];
  };
  std::string cookie(length,0);
  std::generate_n(cookie.begin(), length, randchar);
  return cookie;
}

int g_user_id = 0;

int main() {
  HttpsServer server("server.crt", "server.key");
  server.config.port = 1234;

  MongoDB db;

  server.resource["^/signup$"]["POST"] = [&db](shared_ptr<HttpsServer::Response> response, shared_ptr<HttpsServer::Request> request) {
    try {
      ptree iptree;
      read_json(request->content, iptree);

      ptree doc;
      try {
	ptree query;
	query.put("cookie", iptree.get<string>("cookie"));
	db.findOne("Users", query);

	doc.put("id", g_user_id++);
	doc.put("user", iptree.get<string>("user"));
	doc.put("password", iptree.get<string>("password"));
	db.insert("Users", doc);
      }
      catch (const exception &e) {
	doc.put("id", g_user_id++);
	doc.put("user", iptree.get<string>("user"));
	doc.put("password", iptree.get<string>("password"));
	db.insert("Users", doc);
      }

      ptree optree;
      optree.put("status", "ok");
      optree.put("id", g_user_id);
      std::string json;

      std::stringstream ss;
      write_json(ss, optree);

      std::cout << ss.str() << std::endl;
      response->write(ss);
    }
    catch (const exception &e) {
      response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    }
  };

  server.resource["^/login$"]["POST"] = [&db](shared_ptr<HttpsServer::Response> response, shared_ptr<HttpsServer::Request> request) {
    try {
      ptree iptree;
      read_json(request->content, iptree);

      ptree optree;
      try {
	ptree query;
	query.put("user", iptree.get<string>("user"));
	query.put("password", iptree.get<string>("password"));
	ptree user = db.findOne("Users", query);

	user.put("cookie", GenCookie());
	db.update("Users", query, user);
	optree.put("status", "ok");
      }
      catch (const exception &e) {
	optree.put("status", "ko");
      }

      optree.put("id", g_user_id);
      std::string json;
      write_json(json, optree);
      response->write(json);
    }
    catch (const exception &e) {
      response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    }
  };

  //server.on_error = [](shared_ptr<HttpsServer::Request> [>request*/, const SimpleWeb::error_code & /*ec<]) {
  //// Handle errors here
  //};

  boost::thread server_thread([&server]() {server.start();});

  server_thread.join();
  return 0;
}
