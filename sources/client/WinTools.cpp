//
// Created by hamon_e on 10/15/17.
//

#include <Windows.h>
#include <string>
#include <iostream>

namespace WinTools {
  bool addToStartUp(std::string const &name, std::string const &path, std::string const &args = "") {
    std::string value;
    HKEY hKey = NULL;
    bool res = true;

    value += "\"" + path + "\" " + args;

    if (!RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                         0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL))
      res = true;

    if (res)
      if (!RegSetValueExA(hKey, name.c_str(), 0, REG_SZ,
                          reinterpret_cast<BYTE *>(const_cast<char *>(value.c_str())), value.length()))
        res = true;

    if (hKey)
      RegCloseKey(hKey);

    return res;
  }

  bool addToStartUp(std::string const &name, std::string const &args) {
    char path[MAX_PATH];

    GetModuleFileNameA(NULL, path, MAX_PATH);
    return addToStartUp(name, path, args);
  }
}
