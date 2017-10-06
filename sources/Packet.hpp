#pragma once

#include <sstream>
#include <ostream>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>

#include "EnumClassHash.hpp"
#include "json.hpp"

class Packet {
public:
    enum class Field {
        ID,
        COOKIE,
        CHECKSUM,
        TIMESTAMP,
        PART,
        TOTALPART,
        DATA,
    };

    static std::size_t const defaultSize = 1024;
    static char const partSeparator = '|';

    static const std::unordered_map<Packet::Field, std::string, EnumClassHash> fields;

    using PartPair = std::pair<std::size_t, std::size_t>;

public:
    Packet() = default;
    Packet(boost::property_tree::ptree const &);
    Packet(std::string const &data);

public:
    void set(Packet::Field field, std::string const &value);
    void set(Packet::Field field, std::string &&value);

    template<Field field, typename T>
    T get() const {
        return this->_ptree.get<T>(Packet::fields.at(field));
    }
    template<Field field, typename T>
    T get(T defaultValue) const {
        return this->_ptree.get<T>(Packet::fields.at(field), defaultValue);
    }

    boost::property_tree::ptree const getPtree() const;

public:
    void updateChecksum();
    bool checksum() const;
    PartPair getPartPair() const;

public:
    std::string stringify(bool pretty = false) const;

public:
    std::vector<Packet> split(std::size_t size = Packet::defaultSize) const;
    static Packet join(std::vector<boost::property_tree::ptree> &packets);

private:
    std::string calcChecksum() const;

private:
    boost::property_tree::ptree _ptree;
};

std::ostream &operator<<(std::ostream &stream, Packet const &packet);
