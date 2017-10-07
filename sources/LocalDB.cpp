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

void LocalDB::loop(directory_iterator &it,
                   std::function<bool(directory_iterator &)> ft) {
    directory_iterator end_it;

    for (; it != end_it; ++it) {
        if (is_regular_file(it->path())
            && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            if (!ft(it)) {
                break;
            }
        }
    }

}

void LocalDB::insert(ptree const &doc) {
    boost::mutex::scoped_lock lock(this->_mutex);

    try {
        std::string filename = doc.get<std::string>("checksum") + ".json";
        boost::property_tree::write_json(filename, doc);
    } catch (boost::property_tree::json_parser_error &error) {

    }
}

boost::property_tree::ptree LocalDB::findOne(ptree const &query) {
    ptree result;
    bool found = false;
    path targetDir(".");
    directory_iterator it(targetDir);

    boost::mutex::scoped_lock lock(this->_mutex);
    this->loop(it, [this, &result, &found, &query](directory_iterator &it) -> bool {
        try {
            boost::property_tree::read_json(it->path().string(), result);
            if (this->searchQuery(const_cast<ptree &>(query), result)) {
                found = true;
                return false;
            }
        } catch (boost::property_tree::json_parser_error &error) {

        }
        return true;
    });

    if (found) {
        return result;
    } else {
        throw std::out_of_range("No corresponding file");
    }
}

std::vector<boost::property_tree::ptree> LocalDB::find(ptree const &query) {
    std::vector<ptree> result;
    path targetDir(".");
    directory_iterator it(targetDir);

    boost::mutex::scoped_lock lock(this->_mutex);
    this->loop(it, [this, &result, query](directory_iterator &it) -> bool {
        ptree tmp;

        try {
            boost::property_tree::read_json(it->path().string(), tmp);
            if (this->searchQuery(const_cast<ptree &>(query), tmp))
                result.push_back(tmp);
        } catch (boost::property_tree::json_parser_error &error) {

        }
        return true;
    });
    return result;
}

void LocalDB::update(ptree const &query, ptree const &update) {
    path targetDir(".");
    directory_iterator it(targetDir);

    boost::mutex::scoped_lock lock(this->_mutex);
    this->loop(it, [this, &query, &update](directory_iterator &it) -> bool {
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
        return true;
    });
}

void LocalDB::remove(ptree const &query) {
    path targetDir(".");
    directory_iterator it(targetDir);

    boost::mutex::scoped_lock lock(this->_mutex);
    this->loop(it, [this, &query](directory_iterator &it) -> bool {
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
        return true;
    });
}