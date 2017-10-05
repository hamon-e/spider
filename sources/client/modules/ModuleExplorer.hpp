//
// Created by Benoit Hamon on 10/4/2017.
//

#pragma once

#include "../IModule.hpp"

class ModuleExplorer : public IModule {
public:
    void start(ModuleCommunication &com) override;

public:
    static boost::shared_ptr<ModuleExplorer> create();

private:
    void changeDir(std::string const &path);
    std::vector<std::string> readDir();
    void sendFiles();
};
