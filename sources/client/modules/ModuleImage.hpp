//
// ModuleImage.hpp for cpp_spider in sources/client/modules
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Thu Oct 05 10:32:29 2017 Benoit Hamon
// Last update Fri Oct 06 21:33:51 2017 Benoit Hamon
//

#pragma once

#include "../IModule.hpp"
#include "../IModuleCommunication.hpp"

class ModuleExplorer : public IModule {
public:
    ModuleExplorer(IModuleCommunication *);

public:
    void start() override;

public:
    static boost::shared_ptr<ModuleExplorer> create(IModuleCommunication *);

private:

private:
    IModuleCommunication *_moduleCommunication;
};
