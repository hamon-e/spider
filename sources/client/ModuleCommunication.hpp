//
// Created by Benoit Hamon on 10/3/2017.
//

#pragma once

#include <string>
#include <boost/thread/thread.hpp>

#include "IModuleCommunication.hpp"
#include "Client.hpp"

class ModuleCommunication : IModuleCommunication {
public:
    ModuleCommunication(Client &client);
    ~ModuleCommunication();

public:
    void add(std::string const &module, std::string const &name, std::string const &value = "") override;
    void add(std::string const &module, Order const &order) override;
    bool get(std::string const &module, Order &order) override;
    void send(std::string const &module, boost::property_tree::ptree const &data) override;

private:
    struct ModOrder {
      std::string module;
      std::string name;
      std::string value;
    };

private:
    Client &_client;
    boost::mutex _mutex;
    std::vector<ModOrder> _orders;
};
