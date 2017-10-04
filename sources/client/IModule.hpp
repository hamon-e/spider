//
// Created by Benoit Hamon on 10/3/2017.
//

#pragma once

#include <string>

class ModuleCommunication {
public:
    ModuleCommunication() {};
    ~ModuleCommunication() {};

public:
    struct Order {
        std::string name;
        std::string value;
    };

public:
    void add(std::string const &module, std::string const &name, std::string const &value = "");
    void add(std::string const &module, Order const &order);
    Order get(std::string const &module);
};

class IModule {
public:
    virtual void start(ModuleCommunication &com) = 0;
    virtual void stop() = 0;

public:
    virtual void setParams() = 0;
    virtual void setParams(std::string const &name, std::string const &value) = 0;
};