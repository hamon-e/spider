//
// Created by hamon_e on 10/15/17.
//

#pragma once

#include "SimpleWebServer/client_https.hpp"
#include "SimpleWebServer/server_https.hpp"
#include "SimpleWebServer/crypto.hpp"

#include "IDataBase.hpp"
#include "Server.hpp"

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;
using Crypto = SimpleWeb::Crypto;

namespace pt = boost::property_tree;

class HttpServer {
  public:
    HttpServer(IDataBase *db, Server *server, int port = 443,
               std::string const &certificate = "server.crt",
               std::string const &key = "server.key");

  public:
    void start();
    void join();

  private:
    void signup(std::shared_ptr<HttpsServer::Response> response,
                std::shared_ptr<HttpsServer::Request> request);
    void login(std::shared_ptr<HttpsServer::Response> response,
               std::shared_ptr<HttpsServer::Request> request);
    void client_list(std::shared_ptr<HttpsServer::Response> response,
                     std::shared_ptr<HttpsServer::Request> request);
    void send(std::shared_ptr<HttpsServer::Response> response,
              std::shared_ptr<HttpsServer::Request> request);
    void defaultGet(std::shared_ptr<HttpsServer::Response> response,
                    std::shared_ptr<HttpsServer::Request> request);

  private:
    void init();
    std::string genCookie();

  private:
    bool isFirstUser();
    bool isConnected(std::string const &cookie);

  private:
    IDataBase *_db;
    Server *_server;
    HttpsServer _hServer;
    boost::thread _threads;
};
