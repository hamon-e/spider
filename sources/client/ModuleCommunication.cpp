//
// Created by Benoit Hamon on 10/3/2017.
//

#include "ModuleCommunication.hpp"

ModuleCommunication::ModuleCommunication() {}

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

ModuleCommunication::Order ModuleCommunication::get(std::string const &module) {
  Order order;

  this->_mutex.lock();
  for (auto it = this->_orders.begin(); it != this->_orders.end(); ++it) {
    if ((*it).module == module) {
      order = {(*it).name, (*it).value};
      this->_orders.erase(it);
      break;
    }
  }
  this->_mutex.unlock();
  return order;
}
