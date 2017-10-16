#pragma once

#include <unordered_map>

#include "IDataBase.hpp"

class MapDB : public IDataBase {
  public:
    virtual void insert(std::string const &collection, ptree const &doc);
    virtual ptree findOne(std::string const &collection, ptree const &query);
    virtual std::vector<ptree> find(std::string const &collection, ptree const &query);
    virtual void update(std::string const &collection, ptree const &query, ptree const &update, bool upsert = false);
    virtual void remove(std::string const &collection, ptree const &query);

  private:
    static bool cmpQuery(IDataBase::ptree const &doc, IDataBase::ptree const &query);

  private:
    std::unordered_map<std::string, std::vector<IDataBase::ptree>> _db;
};
