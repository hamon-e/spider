//
// Created by gusmin_m on 10/4/17.
//

#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include "LocalDB.hpp"

namespace pt = boost::property_tree;

int main()
{
    pt::ptree tree;

    tree.put("timestamp", 1);
    tree.put("checksum", 3);
    tree.put("id", 1);
    tree.put("data.key", "qeqqeweqwe");
    tree.put("data.process", "skype");

    pt::ptree tree2;

    tree2.put("timestamp", 2);
    tree.put("checksum", 5);
    tree2.put("data.key", "qeqqeweqwe");
    tree2.put("data.process", "discord");
    tree2.put("id", 2);

    pt::ptree query;
    query.put("timestamp", 1);

    pt::ptree update;
    update.put("data.process", "teamspeak");

    LocalDB db;

    db.insert(tree);
//    db.insert(tree2);

    std::vector<boost::property_tree::ptree> toto = db.find(query);

    std::cout << toto.size() << std::endl;

    db.update(query, update);

    //   db.remove(query);
}