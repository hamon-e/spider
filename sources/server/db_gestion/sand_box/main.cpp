#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <bsoncxx/builder/stream/array.hpp>
#include <string>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using ptree = boost::property_tree::ptree;

mongocxx::client *_mongodb_client;
mongocxx::collection _collection;
//bsoncxx::builder::stream::array _arr;
std::string first;
//bsoncxx::document::value _doc_contents;
mongocxx::database _db_access;
bsoncxx::builder::stream::document _builder;
bsoncxx::builder::stream::document _builder_bis;
std::string path;
/*
void my_insert(ptree const &doc)
{
    static boost::property_tree::ptree::const_iterator first_node = doc.begin();
    int counter = 0;

    for (boost::property_tree::ptree::const_iterator iter = doc.begin();iter != doc.end(); iter++)
    {
        if (!iter->second.empty())
        {
            _builder << iter->first << bsoncxx::builder::stream::open_document;
            my_insert(iter->second);
            _builder << bsoncxx::builder::stream::close_document;
        }
        else if (iter->first == "")
            _builder << std::to_string(counter++) << iter->second.data();
        else
            _builder << iter->first << iter->second.data();
    }
    if (doc.size() > 0 && first_node == doc.begin())
    {
        auto _doc_contents = _builder << bsoncxx::builder::stream::finalize;
        _collection.insert_one(_doc_contents.view());
    }
}

void update(ptree const &query, ptree const &update)
{

}
*/

void _generate_builder(ptree const &doc)
{
    int counter = 0;

    for (boost::property_tree::ptree::const_iterator iter = doc.begin();iter != doc.end(); iter++)
    {
        if (!iter->second.empty())
        {
            _builder << iter->first << bsoncxx::builder::stream::open_document;
            _generate_builder(iter->second);
            _builder << bsoncxx::builder::stream::close_document;
        }
        else if (iter->first == "")
            _builder << std::to_string(counter++) << iter->second.data();
        else
            _builder << iter->first << iter->second.data();
    }
}


void _generate_builder_update(ptree const &doc)
{
    int counter = 0;

    for (boost::property_tree::ptree::const_iterator iter = doc.begin();iter != doc.end(); iter++)
    {
        if (!iter->second.empty())
        {
            if (path == "")
                path +=  iter->first;
            else
                path += "." + iter->first;
           // _builder_bis << "$set" << bsoncxx::builder::stream::open_document;
            //_builder_bis << iter->first << bsoncxx::builder::stream::open_document;
            _generate_builder(iter->second);
            //_builder_bis << bsoncxx::builder::stream::close_document;
            //_builder_bis << bsoncxx::builder::stream::close_document;
            if (path == iter->first && path != "")
                path.erase(path.end() - std::string(iter->first).size(), path.end());
            else
                path.erase(path.end() - std::string("." + iter->first).size(), path.end());
        }
        else if (iter->first != "")
            _builder_bis << "$set" << open_document << path + iter->first << iter->second.data() << close_document;
    }
}

void my_insert(ptree const &doc)
{
    _generate_builder(doc);
    if (doc.size() > 0)
    {
        auto _doc_contents = _builder << bsoncxx::builder::stream::finalize;
        _collection.insert_one(_doc_contents.view());
    }
}

void my_update(ptree const &query, ptree const &update)
{
    if (query.size() > 0 && update.size() > 0)
    {
        _generate_builder(query);
        _generate_builder_update(update);
        _collection.update_one(_builder << finalize, _builder_bis << finalize);
    }
}

int main(int, char**)
{
    mongocxx::instance inst{};
    _mongodb_client = new mongocxx::client(mongocxx::uri{});
    _collection = (*_mongodb_client)["Devone"]["today"];
    ptree pt;
    ptree pt2;
    read_json("./myjson2.json", pt);
    read_json("./myjson3.json", pt2);

    my_insert(pt);
    my_update(pt, pt2);

   /* mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
    bsoncxx::builder::stream::document document{};
    auto collection = conn["new_dbs"]["testcollection"];
    bsoncxx::builder::stream::document builder;
    builder << "name" << "MongoDB"
            << "type" << "database"
            << "count" << 1;

    builder << "versions" << bsoncxx::builder::stream::open_array
            << "v3.2" << "v3.0" << "v2.6" << bsoncxx::builder::stream::close_array;
         builder   << "info"  << bsoncxx::builder::stream::open_document
            << "x" << 203
            << "y" << 102;
    builder << bsoncxx::builder::stream::close_document;
    bsoncxx::document::value doc_value = builder << bsoncxx::builder::stream::finalize;
    collection.insert_one(doc_value.view());*/
    /*auto collection = conn["e"]["testcollection"];
    document << "hello" << "world";
    std::cout << "ok\n";
    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }*/
}
