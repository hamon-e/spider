#include <stdexcept>

#include "MongoDB.hpp"

MongoDB::MongoDB(std::string const &host, int const &port, std::string const &dbName) {
  mongocxx::instance instance{};
  mongocxx::uri uri("mongodb://" + host + ":" + std::to_string(port));
  this->_mongodbClient = new mongocxx::client(uri);
  this->_dbAccess = (*_mongodbClient)[dbName];
}

MongoDB::~MongoDB() {}

void MongoDB::generateBson(ptree const &doc, bsoncxx::builder::stream::document &bson) {
  for (boost::property_tree::ptree::const_iterator iter = doc.begin();iter != doc.end(); iter++) {
    if (!iter->second.empty()) {
      bson << iter->first << bsoncxx::builder::stream::open_document;
      this->generateBson(iter->second, bson);
      bson << bsoncxx::builder::stream::close_document;
    } else {
      bson << iter->first << iter->second.data();
    }
  }
}

bsoncxx::builder::stream::document MongoDB::generateBson(ptree const &doc) {
  bsoncxx::builder::stream::document bson{};
  this->generateBson(doc, bson);
  return bson;
}

void MongoDB::insert(std::string const &collection, ptree const &doc) {
  boost::mutex::scoped_lock lock(this->_mutex);

  try {
    auto bson = this->generateBson(doc);
    auto _doc_contents = bson << bsoncxx::builder::stream::finalize;
    this->_dbAccess[collection].insert_one(_doc_contents.view());
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
}

std::vector<ptree> MongoDB::find(std::string const &collection, ptree const &query) {
  boost::mutex::scoped_lock lock(this->_mutex);

  bsoncxx::stdx::optional<bsoncxx::document::value> query_result;
  std::string  json_result;
  ptree tmp_ptree;
  std::vector<ptree> ret_ptree;

  try {
    auto bson = this->generateBson(query);
    mongocxx::cursor cursor = this->_dbAccess[collection].find(bson << finalize);
    for (auto doc : cursor) {
      json_result = bsoncxx::to_json(doc);
      boost::iostreams::stream <boost::iostreams::array_source> stream(json_result.c_str(), json_result.size());
      boost::property_tree::read_json(stream, tmp_ptree);
      tmp_ptree.erase("_id");
      ret_ptree.push_back(std::move(tmp_ptree));
    }
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
  return (ret_ptree);
}

ptree MongoDB::findOne(std::string const &collection, ptree const &query) {
  boost::mutex::scoped_lock lock(this->_mutex);

  bsoncxx::stdx::optional<bsoncxx::document::value> query_result;
  std::string json_result;
  ptree ret_ptree;

  auto bson = this->generateBson(query);
  query_result = this->_dbAccess[collection].find_one(bson << bsoncxx::builder::stream::finalize);
  if (query_result) {
    json_result = bsoncxx::to_json(*query_result);
    boost::iostreams::stream <boost::iostreams::array_source> stream(json_result.c_str(), json_result.size());
    boost::property_tree::read_json(stream, ret_ptree);
  } else {
    throw std::out_of_range("findOne");
  }
  ret_ptree.erase("_id");
  return (ret_ptree);
}

void MongoDB::remove(std::string const &collection, ptree const &query) {
  boost::mutex::scoped_lock lock(this->_mutex);

  try {
    auto bson = this->generateBson(query);
    auto result = this->_dbAccess[collection].delete_many(bson << bsoncxx::builder::stream::finalize);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
}

void MongoDB::update(std::string const &collection, ptree const &query, ptree const &update, bool upsert) {
  boost::mutex::scoped_lock lock(this->_mutex);
  boost::property_tree::ptree updater;
  updater.put_child("$set", update);
  try {
    auto bsonQuery = this->generateBson(query) << bsoncxx::builder::stream::finalize;
    auto bsonUpdated = this->generateBson(updater) << bsoncxx::builder::stream::finalize;
    auto result = this->_dbAccess[collection].update_many(bsonQuery.view(), bsonUpdated.view());
    if (upsert && (!result || !result->matched_count())) {
      lock.unlock();
      return this->insert(collection, update);
    }
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
}
