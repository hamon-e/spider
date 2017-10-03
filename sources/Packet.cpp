#include "Packet.hpp"
#include "json.hpp"

std::unordered_map<Packet::Field, std::string, EnumClassHash> const Packet::fields = {
    { Packet::ID, "id" },
    { Packet::CHECKSUM, "checksum" },
    { Packet::TIMESTAMP, "timestamp" },
    { Packet::PART, "part" },
    { Packet::DATA, "data" },
};

std::string Packet::stringify(bool pretty) const {
    return json::stringify(this->_ptree, pretty);
}

void Packet::set(Packet::Field field, std::string &&value) {
    this->_ptree.put(Packet::fields.at(field), value);
}

void Packet::set(Packet::Field field, std::string const &value) {
    this->_ptree.put(Packet::fields.at(field), value);
}

std::vector<Packet> Packet::split(std::size_t size) const {
    std::string data = json::stringify(this->_ptree.get_child(Packet::fields.at(Packet::DATA)), false);
    std::size_t nbPacket = ((data.size() - 1) / size) + 1;
    std::size_t part = 1;
    std::vector<Packet> res(nbPacket);
    std::string partField = "|" + std::to_string(nbPacket);

    for (Packet &packet : res) {
        packet.set(Packet::ID, this->_ptree.get(Packet::fields.at(Packet::ID), "0"));
        packet.set(Packet::TIMESTAMP, "0");
        packet.set(Packet::PART, std::move(std::to_string(part) + partField));
        packet.set(Packet::DATA, std::move(data.substr((part - 1) * size, size)));
        packet.updateChecksum();
        ++part;
    }
    return res;
}

std::string Packet::getChecksum() const {
    std::hash<std::string> hash_fn;
    return std::to_string(hash_fn(this->_ptree.get(Packet::fields.at(Packet::DATA), "")));
}

void Packet::updateChecksum() {
    this->set(Packet::CHECKSUM, this->getChecksum());
}

bool Packet::checksum() {
    return this->getChecksum() == this->_ptree.get(Packet::fields.at(Packet::CHECKSUM), "");
}
