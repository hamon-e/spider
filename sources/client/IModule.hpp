//
// Created by Benoit Hamon on 10/3/2017.
//

#pragma once

#include <string>

#include "ModuleCommunication.hpp"
#include "Client.hpp"

class IModule {
public:
    virtual void start(IModuleCommunication *com) = 0;
};
