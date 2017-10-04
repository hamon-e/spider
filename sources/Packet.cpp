#include <sstream>
#include <boost/property_tree/json_parser.hpp>

#include "Packet.hpp"
#include "json.hpp"

std::unordered_map<Packet::Field, std::string, EnumClassHash> const Packet::fields = {
    { Packet::Field::ID, "id" },
    { Packet::Field::COOKIE, "cookie" },
    { Packet::Field::CHECKSUM, "checksum" },
    { Packet::Field::TIMESTAMP, "timestamp" },
    { Packet::Field::PART, "part" },
    { Packet::Field::DATA, "data" },
};

Packet::Packet(std::string const &data) {
    std::stringstream ss;
    ss << data;
    boost::property_tree::json_parser::read_json(ss, this->_ptree);
}

std::string Packet::stringify(bool pretty) const {
    return json::stringify(this->_ptree, pretty);
}

void Packet::set(Packet::Field field, std::string &&value) {
    this->_ptree.put(Packet::fields.at(field), value);
}

void Packet::set(Packet::Field field, std::string const &value) {
    this->_ptree.put(Packet::fields.at(field), value);
}

Packet::partPair Packet::getPartPair() const {
    Packet::partPair part;
    std::string encoded = this->_ptree.get(Packet::fields.at(Packet::Field::PART), "");
    if (encoded == "") {
        part.first = 0;
        part.second = 0;
    } else {
        std::stringstream ss(encoded);
        char sep;
        ss >> part.first >> sep >> part.second;
    }
    return part;
}

std::vector<Packet> Packet::split(size_t size) const {
    std::string data = json::stringify(this->_ptree.get_child(Packet::fields.at(Packet::Field::DATA)), false);
    size_t nbPacket = ((data.size() - 1) / size) + 1;
    size_t part = 1;
    std::vector<Packet> res(nbPacket);
    std::string partField = "|" + std::to_string(nbPacket);

    for (Packet &packet : res) {
        packet.set(Packet::Field::ID, this->_ptree.get(Packet::fields.at(Packet::Field::ID), "0"));
        packet.set(Packet::Field::TIMESTAMP, "0");
        packet.set(Packet::Field::PART, std::move(std::to_string(part) + partField));
        packet.set(Packet::Field::DATA, std::move(data.substr((part - 1) * size, size)));
        packet.updateChecksum();
        ++part;
    }
    return res;
}

std::string Packet::calcChecksum() const {
    std::hash<std::string> hash_fn;
    return std::to_string(hash_fn(this->_ptree.get(Packet::fields.at(Packet::Field::DATA), "")));
}

void Packet::updateChecksum() {
    this->set(Packet::Field::CHECKSUM, this->calcChecksum());
}

bool Packet::checksum() const {
    return this->calcChecksum() == this->_ptree.get(Packet::fields.at(Packet::Field::CHECKSUM), "");
}

std::ostream &operator<<(std::ostream &stream, Packet const &packet) {
    stream << packet.stringify();
    return stream;
}
