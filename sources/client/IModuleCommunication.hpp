//
// Created by Benoit Hamon on 10/3/2017.
//

#pragma once

#include <string>
#include <boost/thread/thread.hpp>

#include <boost/property_tree/ptree.hpp>

class IModuleCommunication {
public:
    struct Order {
        std::string name;
        std::string value;
    };

public:
    virtual void add(std::string const &module, std::string const &name, std::string const &value = "") = 0;
    virtual void add(std::string const &module, Order const &order) = 0;
    virtual bool get(std::string const &module, Order &order) = 0;
    virtual void send(boost::property_tree::ptree const &data) = 0;
};
