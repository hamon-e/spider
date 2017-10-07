//
// Created by golitij on 03/10/17.
//

#include "MongoDB.hpp"

MongoDB::MongoDB(std::string const &client_name)
{
    _mongodb_client = new mongocxx::client(mongocxx::uri{});
    _db_access = (*_mongodb_client)[client_name];
}

MongoDB::~MongoDB() {}

void MongoDB::_generate_builder(ptree const &doc)
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
        else
            _builder << iter->first << iter->second.data();
    }
}

void MongoDB::insert(std::string const &collection, ptree const &doc)
{
    if (doc.size() > 0)
    {
        _collection = _db_access[collection];
        _generate_builder(doc);
        auto _doc_contents = _builder << bsoncxx::builder::stream::finalize;
        _collection.insert_one(_doc_contents.view());
    }
}

std::vector<ptree> MongoDB::find(std::string const &collection, ptree const &query)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> query_result;
    std::string  json_result;
    ptree   tmp_ptree;
    std::vector<ptree>   ret_ptree;

    if (query.size() > 0)
    {
        _collection = _db_access[collection];
        _generate_builder(query);
        mongocxx::cursor cursor = _collection.find(document{} << finalize);
        for(auto doc : cursor)
        {
            json_result = bsoncxx::to_json(doc);
            boost::iostreams::stream<boost::iostreams::array_source> stream(json_result.c_str(), json_result.size());
            boost::property_tree::read_json(stream, tmp_ptree);
            ret_ptree.push_back(tmp_ptree);
        }
    }
    return (ret_ptree);
}

ptree MongoDB::findOne(std::string const &collection, ptree const &query)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> query_result;
    std::string  json_result;
    ptree   ret_ptree;

    if (query.size() > 0)
    {
        _collection = _db_access[collection];
        _generate_builder(query);
        query_result = _collection.find_one(_builder << bsoncxx::builder::stream::finalize);
        if(query_result)
        {
            json_result = bsoncxx::to_json(*query_result);
            boost::iostreams::stream<boost::iostreams::array_source> stream(json_result.c_str(), json_result.size());
            boost::property_tree::read_json(stream, ret_ptree);
        }
    }
    return (ret_ptree);
}

void MongoDB::remove(std::string const &collection, ptree const &query)
{
    if (query.size() > 0)
    {
        _collection = _db_access[collection];
        _generate_builder(query);
        _collection.delete_one(_builder << bsoncxx::builder::stream::finalize);
    }
}

void MongoDB::update(std::string const &collection, ptree const &query, ptree const &update)
{
    ptree tree = update;
    ptree query_bis = query;

    if (query.size() > 0 && update.size() > 0)
    {
        //updatePTree(query_bis, tree);
        //my_remove(update);
        this->insert(collection, tree);
    }
}
