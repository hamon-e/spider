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

    static std::string const dbDirectoryName;

public:
    LocalDB();
    LocalDB(LocalDB const &other) = delete;
    ~LocalDB() = default;
    LocalDB &operator=(LocalDB const &other) = delete;

public:
    virtual ptree findOne(std::string const &collection, ptree const &query);
    virtual std::vector<ptree> find(std::string const &collection, ptree const &query);
    virtual void update(std::string const &collection, ptree const &query, ptree const &update, bool upsert = false);
    virtual void remove(std::string const &collection, ptree const &query);
    virtual void insert(std::string const &collection, ptree const &doc);private:

private:
    void loop(boost::filesystem::directory_iterator &it,
              std::function<bool(boost::filesystem::directory_iterator &)> fn);
    bool searchQuery(ptree &query, ptree const &tree);
};
