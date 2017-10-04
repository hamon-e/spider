//
// Created by Benoit Hamon on 10/3/2017.
//

#pragma once

#include <string>

#include "ModuleCommunication.hpp"

class IModule {
public:
    virtual void start(ModuleCommunication &com) = 0;
    virtual void stop() = 0;

public:
    virtual void setParams() = 0;
    virtual void setParams(std::string const &name, std::string const &value) = 0;
};
