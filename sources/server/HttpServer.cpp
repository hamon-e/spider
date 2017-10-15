//
// Created by hamon_e on 10/15/17.
//

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>
#include "HttpServer.hpp"

HttpServer::HttpServer(IDataBase *db, int port,
                       const std::string &certificate,
                       const std::string &key)
        : _db(db), _server(certificate, key) {
    this->_server.config.port = port;
    this->_id = 0;
    init();
}

void HttpServer::start() {
    this->_threads = boost::thread([this]() {this->_server.start();});
}

void HttpServer::join() {
    this->_threads.join();
}

void HttpServer::init() {
    this->_server.resource["^/signup$"]["POST"] = [this](std::shared_ptr<HttpsServer::Response> response,
                                                         std::shared_ptr<HttpsServer::Request> request) {
        this->signup(response, request);
    };

    this->_server.resource["^/login$"]["POST"] = [this](std::shared_ptr<HttpsServer::Response> response,
                                                        std::shared_ptr<HttpsServer::Request> request) {
        this->login(response, request);
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

void HttpServer::signup(std::shared_ptr<HttpsServer::Response> response,
                        std::shared_ptr<HttpsServer::Request> request) {
    try {
        pt::ptree iptree;
        pt::read_json(request->content, iptree);
        pt::ptree optree;

        try {
            pt::ptree query;
            query.put("id", "0");
            this->_db->findOne("Users", query);
            try {
                pt::ptree query;
                query.put("cookie", iptree.get<std::string>("cookie"));
                this->_db->findOne("Users", query);
                try {
                    pt::ptree doc;
                    doc.put("id", std::to_string(this->_id));
                    doc.put("user", iptree.get<std::string>("user"));
                    doc.put("password", Crypto::md5(iptree.get<std::string>("password")));
                    this->_db->insert("Users", doc);
                    optree.put("status", "ok");
                    optree.put("message", "New user created");
                    optree.put("id", std::to_string(this->_id));
                    ++this->_id;
                } catch (const std::exception &e) {
                    response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
                }
            } catch (const std::exception &e) {
                optree.put("status", "ko");
                optree.put("message", "User not logged in");
                optree.put("ErrorCode", e.what());
            }
        } catch (const std::exception &e) {
            response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
            try {
                pt::ptree doc;
                doc.put("id", std::to_string(this->_id));
                doc.put("user", iptree.get<std::string>("user"));
                doc.put("password", Crypto::md5(iptree.get<std::string>("password")));
                pt::write_json(std::cout, iptree);
                pt::write_json(std::cout, doc);
                pt::write_json(std::cout, doc);
                this->_db->insert("Users", doc);
                optree.put("status", "ok");
                optree.put("message", "New user created");
                optree.put("message", e.what());
                optree.put("id", std::to_string(this->_id));
                ++this->_id;
            } catch (const std::exception &e) {
                response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
            }
        }

        std::stringstream json;
        pt::write_json(json, optree);
        response->write(json);
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
            query.put("password", Crypto::md5(iptree.get<std::string>("password")));
            pt::ptree user = this->_db->findOne("Users", query);
            try {
                std::string cookie = this->genCookie();
                user.put("cookie", cookie);
                this->_db->update("Users", query, user);
                optree.put("status", "ok");
                optree.put("message", "User Connected");
                optree.put("user", iptree.get<std::string>("user"));
                optree.put("id", user.get<std::string>("id"));
                optree.put("cookie", cookie);
            } catch (const std::exception &e) {
                response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
            }
        } catch (const std::exception &e) {
            optree.put("status", "ko");
            optree.put("message", "Bad crementials");
            optree.put("ErrorCode", e.what());
        }

        std::stringstream json;
        pt::write_json(json, optree);
        response->write(json);
    } catch (const std::exception &e) {
        response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    }
}
