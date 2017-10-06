//
// Created by gusmin_m on 10/1/17.
//

#pragma once

#include "ADataBase.hpp"

class LocalDB : public ADataBase {
public:
    virtual ptree findOne(ptree const &query);
    virtual std::vector<ptree> find(ptree const &query);
    virtual void update(ptree const &query, ptree const &update);
    virtual void remove(ptree const &query);
    virtual void insert(ptree const &doc);private:
};