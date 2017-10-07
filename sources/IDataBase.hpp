#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <vector>

class IDataBase {
public:
    using ptree = boost::property_tree::ptree;

    virtual void insert(std::string const &collection, ptree const &doc) = 0;
    virtual ptree findOne(std::string const &collection, ptree const &query) = 0;
    virtual std::vector<ptree> find(std::string const &collection, ptree const &query) = 0;
    virtual void update(std::string const &collection, ptree const &query, ptree const &update) = 0;
    virtual void remove(std::string const &collection, ptree const &query) = 0;
};
