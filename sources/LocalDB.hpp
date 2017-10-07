//
// Created by gusmin_m on 10/1/17.
//

#pragma once

#include <boost/thread/mutex.hpp>
#include <boost/filesystem.hpp>

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
    void loop(boost::filesystem::directory_iterator &it,
              std::function<bool(boost::filesystem::directory_iterator &)> fn);
    bool searchQuery(ptree &query, ptree const &tree);
};