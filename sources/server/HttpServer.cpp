//
// Created by hamon_e on 10/15/17.
//

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>
#include "HttpServer.hpp"
#include "ssl/Base64.hpp"
#include "json.hpp"

HttpServer::HttpServer(IDataBase *db, Server *server, int port,
                       const std::string &certificate,
                       const std::string &key)
        : _db(db), _server(server), _hServer(certificate, key) {
    this->_hServer.config.port = port;
    init();
}

void HttpServer::start() {
    this->_threads = boost::thread([this]() {this->_hServer.start();});
}

void HttpServer::join() {
    this->_threads.join();
}

void HttpServer::init() {
    this->_hServer.resource["^/signup$"]["POST"] = [this](std::shared_ptr<HttpsServer::Response> response,
                                                         std::shared_ptr<HttpsServer::Request> request) {
        this->signup(response, request);
    };

    this->_hServer.resource["^/login$"]["POST"] = [this](std::shared_ptr<HttpsServer::Response> response,
                                                        std::shared_ptr<HttpsServer::Request> request) {
        this->login(response, request);
    };
    this->_hServer.resource["^/client_list$"]["POST"] = [this](std::shared_ptr<HttpsServer::Response> response,
                                                         std::shared_ptr<HttpsServer::Request> request) {
        this->listClients(response, request);
    };
    this->_hServer.default_resource["GET"] = [this](std::shared_ptr<HttpsServer::Response> response,
                                                    std::shared_ptr<HttpsServer::Request> request) {
        this->defaultGet(response, request);
    };
}

std::string HttpServer::genCookie() {
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

bool HttpServer::isFirstUser() {
    pt::ptree query;

    query.put("id", "0");
    try {
        this->_db->findOne("Users", query);
        return false;
    } catch (std::exception) {}
    return true;
}

bool HttpServer::isConnected(std::string const &cookie) {
    pt::ptree query;

    query.put("cookie", cookie);
    try {
        this->_db->findOne("Users", query);
        return true;
    } catch (std::exception) {}
    return false;
}

void HttpServer::signup(std::shared_ptr<HttpsServer::Response> response,
                        std::shared_ptr<HttpsServer::Request> request) {
    try {
        pt::ptree iptree;
        pt::read_json(request->content, iptree);
        pt::ptree optree;

        bool status = true;
        if (!this->isFirstUser()) {
            std::string cookie = iptree.get<std::string>("cookie");
            if (!this->isConnected(cookie))
                status = false;
        }

        if (status) {
            pt::ptree doc;

            doc.put("user", iptree.get<std::string>("user"));
            doc.put("password", Base64::encrypt(Crypto::md5(iptree.get<std::string>("password"))));
            this->_db->insert("Users", doc);
            optree.put("status", "ok");
            optree.put("message", "New user created");
        } else {
            optree.put("status", "ko");
            optree.put("message", "User not logged in");
        }

        response->write(json::stringify(optree));
    } catch (const std::exception &e) {
        response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    }
}

void HttpServer::login(std::shared_ptr<HttpsServer::Response> response,
                       std::shared_ptr<HttpsServer::Request> request) {
   try {
        pt::ptree iptree;
        pt::read_json(request->content, iptree);
        pt::ptree optree;

        try {
            pt::ptree query;
            query.put("user", iptree.get<std::string>("user"));
            query.put("password", Base64::encrypt(Crypto::md5(iptree.get<std::string>("password"))));
            pt::ptree user = this->_db->findOne("Users", query);

            std::string cookie = this->genCookie();
            user.put("cookie", cookie);
            this->_db->update("Users", query, user);
            optree.put("status", "ok");
            optree.put("message", "User Connected");
            optree.put("cookie", cookie);
        } catch (const std::exception &e) {
            optree.put("status", "ko");
            optree.put("message", "Bad credidentials");
        }

        response->write(json::stringify(optree));
    } catch (const std::exception &e) {
        response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    }
}

void HttpServer::listClients(std::shared_ptr<HttpsServer::Response> response,
                             std::shared_ptr<HttpsServer::Request> request) {
    try {
        pt::ptree iptree;
        pt::read_json(request->content, iptree);
        pt::ptree optree;

        if (this->isConnected(iptree.get<std::string>("cookie"))) {
            pt::ptree query;
            pt::ptree res = json::parse(this->_db->find("client", query));

            optree.put("status", "ok");
            optree.add_child("list", res);
        } else {
            optree.put("status", "ko");
        }

        response->write(json::stringify(optree));
    } catch (const std::exception &e) {
        response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    }
}

void HttpServer::defaultGet(std::shared_ptr<HttpsServer::Response> response,
                            std::shared_ptr<HttpsServer::Request> request) {
    try {
        auto web_root_path = boost::filesystem::canonical("web");
        auto path = boost::filesystem::canonical(web_root_path / request->path);

        if (std::distance(web_root_path.begin(), web_root_path.end())
            > std::distance(path.begin(), path.end()) ||
                !std::equal(web_root_path.begin(), web_root_path.end(), path.begin()))
            throw std::invalid_argument("path must be within root path");
        if (boost::filesystem::is_directory(path))
            path /= "index.html";

        auto ifs = std::make_shared<std::ifstream>();
        ifs->open(path.string(), std::ifstream::in | std::ios::binary | std::ios::ate);

        if (*ifs)
            response->write(*ifs);

    } catch(const std::exception &e) {
        response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
    }
}
