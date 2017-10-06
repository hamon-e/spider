//
// Created by gusmin_m on 10/1/17.
//

#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <iostream>

#include "LocalDB.hpp"

using namespace boost::filesystem;

void LocalDB::insert(ptree const &doc) {
    std::string filename = doc.get<std::string>("timestamp") + ".json";

    boost::property_tree::write_json(filename, doc);
}

boost::property_tree::ptree LocalDB::findOne(ptree const &query) {
    ptree result;
    directory_iterator end_it;

    path targetDir(".");

    for (directory_iterator it(targetDir); it != end_it; ++it) {
        std::cout << it->path().string() << std::endl;
        if (is_regular_file(it->path()) && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            boost::property_tree::read_json(it->path().string(), result);
            std::cout << "tata" << std::endl;

            if (this->searchQuery(const_cast<ptree &>(query), result))
                return result;
        }
    }
    throw std::out_of_range("No corresponding file");
}

std::vector<boost::property_tree::ptree> LocalDB::find(ptree const &query) {
    std::vector<ptree> result;
    directory_iterator end_it;

    for (directory_iterator it("."); it != end_it; ++it) {
        if (is_regular_file(it->path()) && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            ptree tmp;

            boost::property_tree::read_json(it->path().string(), tmp);
            if (this->searchQuery(const_cast<ptree &>(query), tmp))
                result.push_back(tmp);
        }
    }
    return result;
}

void LocalDB::update(ptree const &query, ptree const &update) {
    directory_iterator end_it;

    for (directory_iterator it("."); it != end_it; ++it) {
        if (is_regular_file(it->path()) && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            ptree tmp;

            boost::property_tree::read_json(it->path().string(), tmp);
            if (this->searchQuery(const_cast<ptree &>(query), tmp)) {
                this->updatePTree(const_cast<ptree &>(update), tmp);

                boost::property_tree::write_json(it->path().string(), tmp);
            }
        }
    }
}

void LocalDB::remove(ptree const &query) {
    directory_iterator end_it;

    for (directory_iterator it("."); it != end_it; ++it) {
        if (is_regular_file(it->path()) && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            ptree tmp;
            boost::property_tree::read_json(it->path().string(), tmp);

            if (this->searchQuery(const_cast<ptree &>(query), tmp)) {
                boost::filesystem::remove(it->path());
            }
        }
    }
}