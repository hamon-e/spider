//
// Created by Benoit Hamon on 10/3/2017.
//

#pragma once

#include <string>

#include "IModuleCommunication.hpp"

class IModule {
  public:
    virtual void start() = 0;
};
