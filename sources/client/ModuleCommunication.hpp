//
// Created by Benoit Hamon on 10/3/2017.
//

#pragma once

#include <string>
#include <boost/thread/thread.hpp>

class ModuleCommunication {
public:
    ModuleCommunication();
    ~ModuleCommunication();

public:
    struct Order {
        std::string name;
        std::string value;
    };

public:
    void add(std::string const &module, std::string const &name, std::string const &value = "");
    void add(std::string const &module, Order const &order);
    bool get(std::string const &module, Order &order);

private:
    struct ModOrder {
      std::string module;
      std::string name;
      std::string value;
    };

private:
    boost::mutex _mutex;
    std::vector<ModOrder> _orders;
};
