#include <sstream>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "EnumClassHash.hpp"

class Packet {
public:
    static const std::size_t defaultSize = 1024;

enum Field {
    ID,
    CHECKSUM,
    TIMESTAMP,
    PART,
    DATA,
};

public:
    Packet() {

    }

public:
    void set(Packet::Field field, std::string const &value);
    void set(Packet::Field field, std::string &&value);

public:
    std::string stringify(bool pretty) const;

public:
    std::vector<Packet> split(std::size_t size = Packet::defaultSize) const;

public:
    bool checksum() const;

private:
    std::string calcChecksum() const;
    void updateChecksum();

private:
    static const std::unordered_map<Packet::Field, std::string, EnumClassHash> fields;

private:
    boost::property_tree::ptree _ptree;
};
