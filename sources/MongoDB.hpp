//
// Created by golitij on 03/10/17.
//

#ifndef CPP_SPIDER_MongoDB_HPP
#define CPP_SPIDER_MongoDB_HPP

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

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using ptree = boost::property_tree::ptree;

class MongoDB : public IDataBase
{
private:
    mongocxx::client *_mongodb_client;
    mongocxx::database _db_access;
    mongocxx::collection _collection;
    bsoncxx::builder::stream::document _builder;
    boost::mutex _mutex;

public:
    MongoDB(int const &port = 27017, std::string const &db_name = "cpp_spider");
    ~MongoDB();
    virtual void insert(std::string const &collection, ptree const &doc);
    virtual ptree findOne(std::string const &collection, ptree const &query);
    virtual std::vector<ptree> find(std::string const &collection, ptree const &query);
    virtual void update(std::string const &collection, ptree const &query, ptree const &update);
    virtual void remove(std::string const &collection, ptree const &query);

private:
    void _generate_builder(ptree const &doc);
};


#endif //CPP_SPIDER_MongoDB_HPP
