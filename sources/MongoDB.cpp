//
// Created by golitij on 03/10/17.
//

#include "MongoDB.hpp"

MongoDB::MongoDB(int const &port, std::string const &db_name)
{
    mongocxx::instance instance{};
    mongocxx::uri uri("mongodb://localhost:" + std::to_string(port));
    _mongodb_client = new mongocxx::client(uri);
    _db_access = (*_mongodb_client)[db_name];
}

MongoDB::~MongoDB() {}

void MongoDB::_generate_builder(ptree const &doc)
{
    for (boost::property_tree::ptree::const_iterator iter = doc.begin();iter != doc.end(); iter++)
    {
        if (!iter->second.empty())
        {
            this->_builder << iter->first << bsoncxx::builder::stream::open_document;
            this->_generate_builder(iter->second);
            this->_builder << bsoncxx::builder::stream::close_document;
        }
        else
            this->_builder << iter->first << iter->second.data();
    }
}

void MongoDB::insert(std::string const &collection, ptree const &doc)
{
    boost::mutex::scoped_lock lock(this->_mutex);
    try {
        this->_collection = _db_access[collection];
        this->_generate_builder(doc);
        auto _doc_contents = this->_builder << bsoncxx::builder::stream::finalize;
        this->_collection.insert_one(_doc_contents.view());
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}

std::vector<ptree> MongoDB::find(std::string const &collection, ptree const &query)
{
    boost::mutex::scoped_lock lock(this->_mutex);
    bsoncxx::stdx::optional<bsoncxx::document::value> query_result;
    std::string  json_result;
    ptree   tmp_ptree;
    std::vector<ptree>   ret_ptree;

    try {
            this->_collection = _db_access[collection];
            this->_generate_builder(query);
            mongocxx::cursor cursor = this->_collection.find(document{} << finalize);
            for (auto doc : cursor) {
                json_result = bsoncxx::to_json(doc);
                boost::iostreams::stream <boost::iostreams::array_source> stream(json_result.c_str(), json_result.size());
                boost::property_tree::read_json(stream, tmp_ptree);
                ret_ptree.push_back(tmp_ptree);
            }
        }
        catch (std::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
        }
    return (ret_ptree);
}

ptree MongoDB::findOne(std::string const &collection, ptree const &query)
{
    boost::mutex::scoped_lock lock(this->_mutex);
    bsoncxx::stdx::optional<bsoncxx::document::value> query_result;
    std::string  json_result;
    ptree   ret_ptree;

     try {
            this->_collection = _db_access[collection];
            this->_generate_builder(query);
            query_result = this->_collection.find_one(this->_builder << bsoncxx::builder::stream::finalize);
            if (query_result) {
                json_result = bsoncxx::to_json(*query_result);
                boost::iostreams::stream <boost::iostreams::array_source> stream(json_result.c_str(), json_result.size());
                boost::property_tree::read_json(stream, ret_ptree);
            }
        }
        catch (std::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
        }
    return (ret_ptree);
}

void MongoDB::remove(std::string const &collection, ptree const &query)
{
    boost::mutex::scoped_lock lock(this->_mutex);
        try {
            this->_collection = _db_access[collection];
            this->_generate_builder(query);
            this->_collection.delete_one(this->_builder << bsoncxx::builder::stream::finalize);
        }
        catch (std::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
        }
}

void MongoDB::update(std::string const &collection, ptree const &query, ptree const &update)
{
    boost::mutex::scoped_lock lock(this->_mutex);
    try {
            if (this->findOne(collection, query).size() > 0)
            {
                this->remove(collection, query);
                this->insert(collection, update);
            }
        }
   catch (std::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
        }
}