#include <stdexcept>

#include "MapDB.hpp"

void MapDB::insert(std::string const &collection, IDataBase::ptree const &doc) {
    auto node = this->_db.find(collection);
    if (node == this->_db.end()) {
        // this->_db.insert(collection, { 1, doc });
        // this->_db.emplace(collection, std::vector<ptree>(doc));
        this->_db.emplace(collection, std::vector<IDataBase::ptree>(1, doc));
    }
}

bool MapDB::cmpQuery(IDataBase::ptree const &doc, IDataBase::ptree const &query) {
    for (auto field : query) {
        if (doc.get_child(field.first) == field.second) {
            return false;
        }
    }
    return true;
}


IDataBase::ptree MapDB::findOne(std::string const &collection, IDataBase::ptree const &query) {
    auto node = this->_db.find(collection);
    if (node != this->_db.end()) {
        for (auto &doc : node->second) {
            if (MapDB::cmpQuery(doc, query)) {
                return doc;
            }
        }
    }
    throw std::out_of_range("");
}

std::vector<IDataBase::ptree> MapDB::find(std::string const &collection, IDataBase::ptree const &query) {
    std::vector<IDataBase::ptree> res;
    auto node = this->_db.find(collection);
    if (node != this->_db.end()) {
        for (auto &doc : node->second) {
            if (MapDB::cmpQuery(doc, query)) {
                res.push_back(doc);
            }
        }
    }
    return res;
}

void MapDB::update(std::string const &collection, IDataBase::ptree const &query, IDataBase::ptree const &update) {
    auto node = this->_db.find(collection);
    if (node != this->_db.end()) {
        for (auto &doc : node->second) {
            if (MapDB::cmpQuery(doc, query)) {
                doc = update;
                return ;
            }
        }
    }
    throw std::out_of_range("");
}

void MapDB::remove(std::string const &collection, IDataBase::ptree const &query) {
    auto node = this->_db.find(collection);
    if (node != this->_db.end()) {
        for (auto it = node->second.begin(); it != node->second.end();) {
            if (MapDB::cmpQuery(*it, query)) {
                it = node->second.erase(it);
            } else {
                ++it;
            }
        }
    }
    throw std::out_of_range("");
}
