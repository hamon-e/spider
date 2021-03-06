#include "PacketManager.hpp"
#include "tools.hpp"

std::string const PacketManager::partsColName = "parts";
std::string const PacketManager::dataColName = "data";
std::string const PacketManager::waitingColName = "waiting";

PacketManager::PacketManager(IDataBase *db,
                             PacketManager::PacketHandler handler,
                             PacketManager::PacketHandler decryptor,
                             PacketManager::SuccessHandler successHandler,
                             PacketManager::ErrorHandler errorHandler)
        : _handler(handler), _decryptor(decryptor), _errorHandler(errorHandler), _succesHandler(successHandler), _db(db)
{ }

void PacketManager::setDB(IDataBase *db) {
  this->_db = db;
}

#include <iostream>

PacketManager &PacketManager::in(std::string const &data, boost::asio::ip::udp::endpoint &from) {
  try {
    Packet packet(data);
    this->_decryptor(packet);
    if (!packet.checksum()) {
      tools::call(this->_errorHandler, packet, PacketManager::Error::CHECKSUM);
    } else {
      boost::property_tree::ptree query;
      query.put(Packet::fields.at(Packet::Field::ID), packet.get<Packet::Field::ID, std::string>());
      std::string cookie = packet.get<Packet::Field::COOKIE, std::string>();
      if (cookie.empty()) {
        try {
          boost::property_tree::ptree query;
          boost::property_tree::ptree ptree;
          query.put("host", from.address().to_string());
          query.put("port", std::to_string(from.port()));
          ptree = this->_db->findOne("client", query);
          std::cout << "FOUND" << std::endl;
          std::cout << ptree << std::endl;
          packet.set(Packet::Field::COOKIE, ptree.get<std::string>("cookie"));
        } catch (std::exception) {
          packet.set(Packet::Field::COOKIE, from.address().to_string() + ":" + std::to_string(from.port()));
        }
      }
      query.put(Packet::fields.at(Packet::Field::COOKIE), packet.get<Packet::Field::COOKIE, std::string>());
      query.put(Packet::fields.at(Packet::Field::PART), packet.get<Packet::Field::PART, std::string>());
      this->_db->update(PacketManager::partsColName, query, packet.getPtree(), true);
      this->complete(query, from, packet);
    }
  } catch (boost::property_tree::json_parser::json_parser_error &err) {
  }
  return *this;
}

void PacketManager::complete(boost::property_tree::ptree &query, boost::asio::ip::udp::endpoint &from, Packet &part) {
  query.erase(Packet::fields.at(Packet::Field::PART));
  std::vector<boost::property_tree::ptree> packets = this->_db->find(PacketManager::partsColName, query);
  if (!packets.size()) {
    return ;
  }

  if (packets.size() == static_cast<std::size_t>(packets[0].get(Packet::fields.at(Packet::Field::TOTALPART), 0))) {
    try {
      Packet packet = Packet::join(packets);
      boost::property_tree::ptree ptree = packet.getPtree();
      if (ptree.get("data.type", "") != "success") {
        tools::call(this->_succesHandler, part, from);
        this->_handler(packet);
      } else {
        boost::property_tree::ptree tree;
        tree.put(boost::property_tree::ptree::path_type("packet.id", '/'), ptree.get("data.id", ""));
        tree.put(boost::property_tree::ptree::path_type("packet.part", '/'), ptree.get("data.part", ""));
        this->_db->remove(PacketManager::waitingColName, tree);
      }
    } catch (std::exception) {}

    try {
      this->_db->remove(PacketManager::partsColName, query);
    } catch (std::exception &) {}
  } else {
    tools::call(this->_succesHandler, part, from);
  }
}
