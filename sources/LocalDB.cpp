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

bool LocalDB::searchQuery(ptree &query, ptree const &tree) {
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

void LocalDB::insert(ptree const &doc) {
    boost::mutex::scoped_lock lock(this->_mutex);
    std::string filename = doc.get<std::string>("checksum") + ".json";

    try {
        boost::property_tree::write_json(filename, doc);
    } catch (boost::property_tree::json_parser_error &error) {

    }
}

boost::property_tree::ptree LocalDB::findOne(ptree const &query) {
    ptree result;
    directory_iterator end_it;
    path targetDir(".");

    boost::mutex::scoped_lock lock(this->_mutex);
    for (directory_iterator it(targetDir); it != end_it; ++it) {
        if (is_regular_file(it->path())
            && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            try {
                boost::property_tree::read_json(it->path().string(), result);
                if (this->searchQuery(const_cast<ptree &>(query), result))
                    return result;
            } catch (boost::property_tree::json_parser_error &error) {

            }
        }
    }
    throw std::out_of_range("No corresponding file");
}

std::vector<boost::property_tree::ptree> LocalDB::find(ptree const &query) {
    std::vector<ptree> result;
    directory_iterator end_it;

    boost::mutex::scoped_lock lock(this->_mutex);
    for (directory_iterator it("."); it != end_it; ++it) {
        if (is_regular_file(it->path())
            && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            ptree tmp;

            try {
                boost::property_tree::read_json(it->path().string(), tmp);
                if (this->searchQuery(const_cast<ptree &>(query), tmp))
                    result.push_back(tmp);
            } catch (boost::property_tree::json_parser_error &error) {

            }
        }
    }
    return result;
}

void LocalDB::update(ptree const &query, ptree const &update) {
    directory_iterator end_it;

    boost::mutex::scoped_lock lock(this->_mutex);
    for (directory_iterator it("."); it != end_it; ++it) {
        if (is_regular_file(it->path())
            && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            ptree tmp;

            try {
                boost::property_tree::read_json(it->path().string(), tmp);
                if (this->searchQuery(const_cast<ptree &>(query), tmp)) {
                    try {
                        boost::property_tree::write_json(it->path().string(), update);
                    } catch (boost::property_tree::json_parser_error &error) {

                    }
                }
            } catch (boost::property_tree::json_parser_error &error) {

            }
        }
    }
}

void LocalDB::remove(ptree const &query) {
    directory_iterator end_it;

    boost::mutex::scoped_lock lock(this->_mutex);
    for (directory_iterator it("."); it != end_it; ++it) {
        if (is_regular_file(it->path())
            && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            ptree tmp;

            try {
                boost::property_tree::read_json(it->path().string(), tmp);
            } catch (boost::property_tree::json_parser_error &error) {

            }
            if (this->searchQuery(const_cast<ptree &>(query), tmp)) {
                try {
                    boost::filesystem::remove(it->path());
                } catch (boost::filesystem::filesystem_error &error) {

                }
            }
        }
    }
}