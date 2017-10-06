//
// Created by golitij on 03/10/17.
//

#ifndef CPP_SPIDER_DB_GESTION_HPP
#define CPP_SPIDER_DB_GESTION_HPP

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
#include "IDataBase.hpp"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class db_gestion : public IDataBase
{
    mongocxx::client *_mongodb_client;
    mongocxx::database _db_access;
    mongocxx::collection _collection;
    bsoncxx::builder::stream::document _builder;

    void _generate_builder(ptree const &doc);
public:
    db_gestion(std::string const &client_name = "cpp_spider");
    ~db_gestion();
    void insert(ptree const &doc);
    void set_collection_name(std::string const & coll_name = "JoneDoe");
    std::vector<ptree> find(ptree const &query);
    void update(ptree const &query, ptree const &update);
    void remove(ptree const &query);
};


#endif //CPP_SPIDER_DB_GESTION_HPP
