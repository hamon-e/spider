//
// Created by gusmin_m on 10/6/17.
//

#include <boost/foreach.hpp>
#include "ADataBase.hpp"

bool ADataBase::searchQuery(ptree &query, ptree const &tree) {
    BOOST_FOREACH(ptree::value_type &v, query.get_child("")) {
        boost::optional<std::string> field = tree.get_optional<std::string>(v.first);
        if (!field.is_initialized())
            return false;
        if (!v.second.empty())
            return searchQuery(v.second, tree.get_child(v.first));
        if (field.get() != v.second.data()) {
            return false;
        }
    }
    return true;
}

void ADataBase::updatePTree(ptree &update, ptree &tree) {
    BOOST_FOREACH(ptree::value_type &v, update.get_child("")) {
        boost::optional<std::string> field = tree.get_optional<std::string>(v.first);
        if (!field.is_initialized()) {
            ptree test;
            tree.add_child(v.first, test);
        }
        if (!v.second.empty())
            updatePTree(v.second, tree.get_child(v.first));
        tree.put(v.first, v.second.data());
    }
}