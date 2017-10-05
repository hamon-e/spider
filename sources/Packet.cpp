#include <sstream>
#include <boost/property_tree/json_parser.hpp>

#include "Packet.hpp"

std::unordered_map<Packet::Field, std::string, EnumClassHash> const Packet::fields = {
    { Packet::Field::ID, "id" },
    { Packet::Field::COOKIE, "cookie" },
    { Packet::Field::TYPE, "type" },
    { Packet::Field::CHECKSUM, "checksum" },
    { Packet::Field::TIMESTAMP, "timestamp" },
    { Packet::Field::PART, "part" },
    { Packet::Field::TOTALPART, "total" },
    { Packet::Field::DATA, "data" },
};

Packet::Packet(std::string const &data) {
    std::stringstream ss;
    ss << data;
    boost::property_tree::ptree ptree;
    boost::property_tree::json_parser::read_json(ss, ptree);
}

Packet::Packet(boost::property_tree::ptree const &ptree)
    : _ptree(ptree)
{}

std::string Packet::stringify(bool pretty) const {
    return json::stringify(this->_ptree, pretty);
}

void Packet::set(Packet::Field field, std::string &&value) {
    this->_ptree.put(Packet::fields.at(field), value);
}

void Packet::set(Packet::Field field, std::string const &value) {
    this->_ptree.put(Packet::fields.at(field), value);
}

boost::property_tree::ptree const Packet::getPtree() const {
    return this->_ptree;
}

Packet::PartPair Packet::getPartPair() const {
    Packet::PartPair part;

    part.first = this->_ptree.get(Packet::fields.at(Packet::Field::PART), 0);
    part.second = this->_ptree.get(Packet::fields.at(Packet::Field::TOTALPART), 0);
    return part;
}

std::vector<Packet> Packet::split(size_t size) const {
    // std::string data = json::stringify(this->_ptree.get_child(Packet::fields.at(Packet::Field::DATA)), false);
    std::string data = this->_ptree.get(Packet::fields.at(Packet::Field::DATA), "");
    size_t nbPacket = ((data.size() - 1) / size) + 1;
    size_t part = 1;
    std::vector<Packet> res(nbPacket);
    std::string totalPart = std::to_string(nbPacket);

    for (Packet &packet : res) {
        packet.set(Packet::Field::ID, this->_ptree.get(Packet::fields.at(Packet::Field::ID), "0"));
        packet.set(Packet::Field::TIMESTAMP, "0");
        packet.set(Packet::Field::PART, std::move(std::to_string(part)));
        packet.set(Packet::Field::TOTALPART, totalPart);
        packet.set(Packet::Field::DATA, std::move(data.substr((part - 1) * size, size)));
        packet.updateChecksum();
        ++part;
    }
    return res;
}

Packet Packet::join(std::vector<boost::property_tree::ptree> &packets) {
    std::sort(packets.begin(), packets.end(), [](boost::property_tree::ptree const &p1, boost::property_tree::ptree const &p2) {
        return p1.get(Packet::fields.at(Packet::Field::PART), 0) < p2.get(Packet::fields.at(Packet::Field::PART), 0);
    });
    auto it = packets.begin();
    Packet packet(*it);
    ++it;
    std::string data = packet.get<Packet::Field::DATA, std::string>();
    data.resize(data.size() * packets.size());
    for (; it != packets.end(); ++it) {
        data += packet.get<Packet::Field::DATA, std::string>();
    }
    packet.set(Packet::Field::DATA, data);
    return packet;
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
