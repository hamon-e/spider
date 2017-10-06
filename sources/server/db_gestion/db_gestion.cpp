//
// Created by golitij on 03/10/17.
//

#include "db_gestion.hpp"

db_gestion::db_gestion(std::string const &client_name)
{
    _mongodb_client = new mongocxx::client(mongocxx::uri{});
    _db_access = (*_mongodb_client)[client_name];
}

db_gestion::~db_gestion() {}

void db_gestion::_generate_builder(ptree const &doc)
{
    int counter = 0;

    for (boost::property_tree::ptree::const_iterator iter = doc.begin();iter != doc.end(); iter++)
    {
        if (!iter->second.empty())
        {
            _builder << iter->first << bsoncxx::builder::stream::open_document;
            this->_generate_builder(iter->second);
            _builder << bsoncxx::builder::stream::close_document;
        }
        else if (iter->first == "")
            _builder << std::to_string(counter++) << iter->second.data();
        else
            _builder << iter->first << iter->second.data();
    }
}

void db_gestion::set_collection_name(std::string const & coll_name)
{
    _collection = _db_access[coll_name];
}

void db_gestion::insert(ptree const &doc)
{
    if (doc.size() > 0)
    {
        _generate_builder(doc);
        auto _doc_contents = _builder << bsoncxx::builder::stream::finalize;
        _collection.insert_one(_doc_contents.view());
    }
}

std::vector<ptree> db_gestion::find(ptree const &query)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> query_result;
    std::string  json_result;
    ptree   tmp_ptree;
    std::vector<ptree>   ret_ptree;

    if (query.size() > 0)
    {
        this->_generate_builder(query);
        query_result = _collection.find_one(_builder << bsoncxx::builder::stream::finalize);
        if(query_result)
        {
            json_result = bsoncxx::to_json(*query_result);
            boost::iostreams::stream<boost::iostreams::array_source> stream(json_result.c_str(), json_result.size());
            boost::property_tree::read_json(stream, tmp_ptree);
            ret_ptree.push_back(tmp_ptree);
            return (ret_ptree);
        }
    }
    return (NULL);
}

void db_gestion::update(ptree const &query, ptree const &update)
{
    bsoncxx::builder::stream::document query_builder;
    bsoncxx::builder::stream::document update_builder;

    if (query.size() > 0 && update.size() > 0)
    {
        this->_generate_builder(query);
        query_builder = _builder;
        this->_generate_builder(update);
        update_builder = _builder;
        _collection.update_one(query_builder << finalize, bsoncxx::builder::stream::document() << "$set" << open_document << update_builder << close_document << finalize);
    }
}

void db_gestion::remove(ptree const &query)
{
}
