//
// Created by gusmin_m on 10/1/17.
//

#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <iostream>

#include "LocalDB.hpp"
#include "Packet.hpp"

using namespace boost::filesystem;

std::string const LocalDB::dbDirectoryName = "DB";

LocalDB::LocalDB()
{
    path dbDirectory(LocalDB::dbDirectoryName);
    try {
        if (!exists(dbDirectory)) {
            create_directory(dbDirectory);
        }
    } catch (std::exception &) {

    }
}

bool LocalDB::searchQuery(ptree const &query, ptree const &tree) const {
    for (ptree::value_type v : query.get_child("")) {
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

void LocalDB::foreachJsonFile(boost::filesystem::directory_iterator &it,
                              std::function<bool(boost::filesystem::directory_iterator &)> fn) const
{
    directory_iterator end_it;

    for (; it != end_it; ++it) {
        if (is_regular_file(it->path())
            && it->path().string().substr(it->path().string().find_last_of('.') + 1) == "json") {
            if (!fn(it)) {
                break;
            }
        }
    }
}

void LocalDB::insert(std::string const &collection, ptree const &doc) {
    boost::mutex::scoped_lock lock(this->_mutex);

    std::string const collectionPath = LocalDB::dbDirectoryName + "/" + collection;
    path targetDir(collectionPath);
    try {
        if (!exists(targetDir)) {
            create_directory(targetDir);
        }

        std::string filename = collectionPath
                               + "/"
                               + doc.get<std::string>(Packet::fields.at(Packet::Field::ID))
                               + "_"
                               + doc.get<std::string>(Packet::fields.at(Packet::Field::TIMESTAMP))
                               + "_"
                               + doc.get<std::string>(Packet::fields.at(Packet::Field::PART))
                               + ".json";

        boost::property_tree::write_json(filename, doc);
    } catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }
}

boost::property_tree::ptree LocalDB::findOne(std::string const &collection, ptree const &query) {
    boost::mutex::scoped_lock lock(this->_mutex);

    ptree result;
    bool found = false;

    std::string const collectionPath = LocalDB::dbDirectoryName + "/" + collection;
    path targetDir(collectionPath);
    if(!exists(targetDir)) {
        create_directory(targetDir);
    }
    directory_iterator it(targetDir);

    this->foreachJsonFile(it, [this, &result, &found, &query](directory_iterator &it) -> bool {
        try {
            boost::property_tree::read_json(it->path().string(), result);
            if (this->searchQuery(query, result)) {
                found = true;
                return false;
            }
        } catch (std::exception &) {

        }
        return true;
    });

    if (found) {
        return result;
    } else {
        throw std::out_of_range("No corresponding file");
    }
}

std::vector<boost::property_tree::ptree> LocalDB::find(std::string const &collection, ptree const &query) {
    boost::mutex::scoped_lock lock(this->_mutex);

    std::vector<ptree> result;

    std::string const collectionPath = LocalDB::dbDirectoryName + "/" + collection;
    path targetDir(collectionPath);
    if(!exists(targetDir)) {
        create_directory(targetDir);
    }
    directory_iterator it(targetDir);

    this->foreachJsonFile(it, [this, &result, query](directory_iterator &it) -> bool {
        ptree tmp;

        try {
            boost::property_tree::read_json(it->path().string(), tmp);
            if (this->searchQuery(query, tmp))
                result.push_back(tmp);
        } catch (std::exception &) {

        }
        return true;
    });
    return result;
}

void LocalDB::update(std::string const &collection, ptree const &query, ptree const &update) {
    boost::mutex::scoped_lock lock(this->_mutex);

    std::string const collectionPath = LocalDB::dbDirectoryName + "/" + collection;
    path targetDir(collectionPath);
    if(!exists(targetDir)) {
        create_directory(targetDir);
    }
    directory_iterator it(targetDir);

    this->foreachJsonFile(it, [this, &query, &update](directory_iterator &it) -> bool {
        ptree tmp;

        try {
            boost::property_tree::read_json(it->path().string(), tmp);
            if (this->searchQuery(query, tmp)) {
                boost::property_tree::write_json(it->path().string(), update);
            }
        } catch (std::exception &) {

        }
        return true;
    });
}

void LocalDB::remove(std::string const &collection, ptree const &query) {
    boost::mutex::scoped_lock lock(this->_mutex);

    std::string const collectionPath = LocalDB::dbDirectoryName + "/" + collection;
    path targetDir(collectionPath);
    if(!exists(targetDir)) {
        create_directory(targetDir);
    }
    directory_iterator it(targetDir);

    this->foreachJsonFile(it, [this, &query](directory_iterator &it) -> bool {
        ptree tmp;

        try {
            boost::property_tree::read_json(it->path().string(), tmp);

            if (this->searchQuery(query, tmp)) {
                boost::filesystem::remove(it->path());
            }
        } catch (std::exception &) {

        }
        return true;
    });
}