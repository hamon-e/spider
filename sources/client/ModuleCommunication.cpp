//
// Created by Benoit Hamon on 10/3/2017.
//

#include "ModuleCommunication.hpp"

ModuleCommunication::ModuleCommunication(Client &client) : _client(client) {}

ModuleCommunication::~ModuleCommunication() {}

void ModuleCommunication::add(std::string const &module,
			      std::string const &name,
			      std::string const &value) {
  this->_mutex.lock();
  this->_orders.push_back({module, name, value});
  this->_mutex.unlock();
}

void ModuleCommunication::add(std::string const &module, Order const &order) {
  this->add(module, order.name, order.value);
}

void ModuleCommunication::add(boost::property_tree::ptree const &ptree) {
  this->add(ptree.get<std::string>("module"),
	    ptree.get<std::string>("name"),
	    ptree.get<std::string>("value"));
};

bool ModuleCommunication::get(std::string const &module, Order &order) {
  this->_mutex.lock();
  for (auto it = this->_orders.begin(); it != this->_orders.end(); ++it) {
    if ((*it).module == module) {
      order = {(*it).name, (*it).value};
      this->_orders.erase(it);
      this->_mutex.unlock();
      return true;
    }
  }
  this->_mutex.unlock();
  return false;
}

void ModuleCommunication::send(boost::property_tree::ptree const &data) {
  std::stringstream ss;
  boost::property_tree::json_parser::write_json(ss, data);

  this->_client.send(ss.str());
  std::cout << ss.str() << std::endl;
}
