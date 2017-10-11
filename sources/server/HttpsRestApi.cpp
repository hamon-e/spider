//
// HttpsRestApi.cpp for cpp_spider in sources/server
//
// Made by Nicolas Goudal
// Login   <nicolas.goudal@epitech.eu>
//
// Started on  Sun Oct 08 18:38:49 2017 Nicolas Goudal
// Last update Mon Oct 09 00:34:48 2017 Nicolas Goudal
//

#include "SimpleWebServer/client_https.hpp"
#include "SimpleWebServer/server_https.hpp"
#include "SimpleWebServer/crypto.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

#include "MongoDB.hpp"

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;
using Crypto = SimpleWeb::Crypto;
namespace pt = boost::property_tree;

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
  server.config.port = 443;

  MongoDB db;

  server.resource["^/signup$"]["POST"] = [&db](std::shared_ptr<HttpsServer::Response> response,
					       std::shared_ptr<HttpsServer::Request> request) {
    try {
      pt::ptree iptree;
      pt::read_json(request->content, iptree);
      pt::ptree optree;

      try {
	pt::ptree query;
	query.put("id", "0");
	db.findOne("Users", query);
	try {
	  pt::ptree query;
	  query.put("cookie", iptree.get<std::string>("cookie"));
	  db.findOne("Users", query);
	  try {
	    pt::ptree doc;
	    doc.put("id", std::to_string(g_user_id));
	    doc.put("user", iptree.get<std::string>("user"));
	    doc.put("password", Crypto::md5(iptree.get<std::string>("password")));
	    db.insert("Users", doc);
	    optree.put("status", "ok");
	    optree.put("message", "New user created");
	    optree.put("id", std::to_string(g_user_id));
	    ++g_user_id;
	  }
	  catch (const std::exception &e) {
	    response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
	  }
	}
	catch (const std::exception &e) {
	  optree.put("status", "ko");
	  optree.put("message", "User not logged in");
	  optree.put("ErrorCode", e.what());
	}
      }
      catch (const std::exception &e) {
	response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
	try {
	  pt::ptree doc;
	  doc.put("id", std::to_string(g_user_id));
	  doc.put("user", iptree.get<std::string>("user"));
	  doc.put("password", Crypto::md5(iptree.get<std::string>("password")));
	  pt::write_json(std::cout, iptree);
	  pt::write_json(std::cout, doc);
	  pt::write_json(std::cout, doc);
	  db.insert("Users", doc);
	  optree.put("status", "ok");
	  optree.put("message", "New user created");
	  optree.put("message", e.what());
	  optree.put("id", std::to_string(g_user_id));
	  ++g_user_id;
	}
	catch (const std::exception &e) {
	  response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
	}
      }

      std::stringstream json;
      pt::write_json(json, optree);
      response->write(json);
    }
    catch (const std::exception &e) {
      response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    }
  };

  server.resource["^/login$"]["POST"] = [&db](std::shared_ptr<HttpsServer::Response> response,
					      std::shared_ptr<HttpsServer::Request> request) {
    try {
      pt::ptree iptree;
      pt::read_json(request->content, iptree);
      pt::ptree optree;

      try {
	pt::ptree query;
	query.put("user", iptree.get<std::string>("user"));
	query.put("password", Crypto::md5(iptree.get<std::string>("password")));
	pt::ptree user = db.findOne("Users", query);
	try {
	  std::string cookie = GenCookie();
	  user.put("cookie", cookie);
	  db.update("Users", query, user);
	  optree.put("status", "ok");
	  optree.put("message", "User Connected");
	  optree.put("user", iptree.get<std::string>("user"));
	  optree.put("id", user.get<std::string>("id"));
	  optree.put("cookie", cookie);
	}
	catch (const std::exception &e) {
	  response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
	}
      }
      catch (const std::exception &e) {
	optree.put("status", "ko");
	optree.put("message", "Bad crementials");
	optree.put("ErrorCode", e.what());
      }

      std::stringstream json;
      pt::write_json(json, optree);
      response->write(json);
    }
    catch (const std::exception &e) {
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
