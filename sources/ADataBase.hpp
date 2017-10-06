//
// Created by gusmin_m on 10/6/17.
//

#pragma once

#include "IDataBase.hpp"

class ADataBase : public IDataBase {
public:
    virtual void insert(ptree const &doc) = 0;
    virtual ptree findOne(ptree const &query) = 0;
    virtual std::vector<ptree> find(ptree const &query) = 0;
    virtual void update(ptree const &query, ptree const &update) = 0;
    virtual void remove(ptree const &query) = 0;

protected:
    bool searchQuery(ptree &query, ptree const &tree);
    void updatePTree(ptree &update, ptree &tree);
};