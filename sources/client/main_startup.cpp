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

BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
  HKEY hKey = NULL;
  LONG lResult = 0;
  BOOL fSuccess = TRUE;
  DWORD dwSize;

  const size_t count = MAX_PATH * 2;
  wchar_t szValue[count] = {};


  wcscpy_s(szValue, count, L"\"");
  wcscat_s(szValue, count, pathToExe);
  wcscat_s(szValue, count, L"\" ");

  if (args != NULL)
  {
    // caller should make sure "args" is quoted if any single argument has a space
    // e.g. (L"-name \"Mark Voidale\"");
    wcscat_s(szValue, count, args);
  }

  lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

  fSuccess = (lResult == 0);

  if (fSuccess)
  {
    dwSize = (wcslen(szValue)+1)*2;
    lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
    fSuccess = (lResult == 0);
  }

  if (hKey != NULL)
  {
    RegCloseKey(hKey);
    hKey = NULL;
  }

  return fSuccess;
}

void RegisterProgram()
{
  wchar_t szPathToExe[MAX_PATH];

  GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
  RegisterMyProgramForStartup(L"My_Program", szPathToExe, L"-foobar");
}

int main(int argc, char *argv[]) {

  return 0;
}
