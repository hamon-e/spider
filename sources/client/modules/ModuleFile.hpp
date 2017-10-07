//
// Created by Benoit Hamon on 10/4/2017.
//

#pragma once

#include "../IModule.hpp"
#include "../IModuleCommunication.hpp"

class ModuleFile : public IModule {
public:
    ModuleFile(IModuleCommunication *);

public:
    void start() override;

public:
    static boost::shared_ptr<ModuleFile> create(IModuleCommunication *);

private:
    void sendFile(std::string const &file);

private:
    IModuleCommunication *_moduleCommunication;
};
