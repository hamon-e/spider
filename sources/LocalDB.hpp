//
// Created by gusmin_m on 10/1/17.
//

#pragma once

#include <boost/thread/mutex.hpp>

#include "IDataBase.hpp"

class LocalDB : public IDataBase {
private:
    boost::mutex _mutex;

public:
    virtual ptree findOne(ptree const &query);
    virtual std::vector<ptree> find(ptree const &query);
    virtual void update(ptree const &query, ptree const &update);
    virtual void remove(ptree const &query);
    virtual void insert(ptree const &doc);private:

private:
    bool searchQuery(ptree &query, ptree const &tree);
};