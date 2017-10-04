#pragma once

#include <sstream>
#include <ostream>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>

#include "EnumClassHash.hpp"

class Packet {
public:
    static std::size_t const defaultSize = 1024;
    static char const partSeparator = '|';

    using partPair = std::pair<std::size_t, std::size_t>;

enum class Field {
    ID,
    COOKIE,
    CHECKSUM,
    TIMESTAMP,
    PART,
    DATA,
};

public:
    Packet() {}
    Packet(std::string const &data);
public:
    void set(Packet::Field field, std::string const &value);
    void set(Packet::Field field, std::string &&value);

public:
    bool checksum() const;
    std::pair<std::size_t, std::size_t>getPartPair() const;

public:
    std::string stringify(bool pretty = false) const;

public:
    std::vector<Packet> split(std::size_t size = Packet::defaultSize) const;

private:
    std::string calcChecksum() const;
    void updateChecksum();

private:
    static const std::unordered_map<Packet::Field, std::string, EnumClassHash> fields;

private:
    boost::property_tree::ptree _ptree;
};

std::ostream &operator<<(std::ostream &stream, Packet const &packet);
