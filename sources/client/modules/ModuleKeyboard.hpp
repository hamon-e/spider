//
// Created by Benoit Hamon on 10/4/2017.
//

#pragma once

#include "../IModule.hpp"

class ModuleKeyboard : public IModule {
public:
    void start(ModuleCommunication &com) override;
    void stop() override;
    void setParams() override;
    void setParams(std::string const &name, std::string const &value) override;

public:
    static boost::shared_ptr<ModuleKeyboard> create();

public:
    static LRESULT CALLBACK hookCallback(int nCode, WPARAM wParam, LPARAM lParam);
};
