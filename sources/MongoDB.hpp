#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/thread/mutex.hpp>
#include "IDataBase.hpp"
#include "LocalDB.hpp"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using ptree = boost::property_tree::ptree;

class MongoDB : public IDataBase {
  private:
    mongocxx::client *_mongodbClient;
    mongocxx::database _dbAccess;
    boost::mutex _mutex;

  public:
    MongoDB(std::string const &host = "",
            int const &port = 27017,
            std::string const &dbName = "cpp_spider");
    ~MongoDB();

  public:
    virtual void insert(std::string const &collection, ptree const &doc);
    virtual ptree findOne(std::string const &collection, ptree const &query);
    virtual std::vector<ptree> find(std::string const &collection, ptree const &query);
    virtual void update(std::string const &collection, ptree const &query, ptree const &update, bool upsert = false);
    virtual void remove(std::string const &collection, ptree const &query);

  private:
    bsoncxx::builder::stream::document generateBson(ptree const &doc);
    void generateBson(ptree const &doc, bsoncxx::builder::stream::document &bson);
};
