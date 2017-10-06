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

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

int main()
{
    mongocxx::instance _instance;
    mongocxx::client _mongodb_client(mongocxx::uri());
    mongocxx::database _db_access;
    mongocxx::collection _collection;
    auto builder = bsoncxx::builder::stream::document();

    _db_access = _mongodb_client[_client_name];
    bsoncxx::document::value doc_value = builder
            << "name" << "MongoDB"
            << "type" << "database"
            << "count" << 1
            << "versions" << bsoncxx::builder::stream::open_array
            << "v3.2" << "v3.0" << "v2.6"
            << close_array
            << "info" << bsoncxx::builder::stream::open_document
            << "x" << 203
            << "y" << 102
            << bsoncxx::builder::stream::close_document
            << bsoncxx::builder::stream::finalize;

}