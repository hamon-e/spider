//
// Created by hamon_e on 10/15/17.
//

#pragma once

#include "SimpleWebServer/client_https.hpp"
#include "SimpleWebServer/server_https.hpp"
#include "SimpleWebServer/crypto.hpp"

#include "IDataBase.hpp"

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;
using Crypto = SimpleWeb::Crypto;

namespace pt = boost::property_tree;

class HttpServer {
public:
    HttpServer(IDataBase *db, int port = 443,
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

private:
    void init();
    std::string genCookie();

private:
    IDataBase *_db;
    HttpsServer _server;
    boost::thread _threads;
    int _id;
};
