//
// Base64.hpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Mon Oct 02 16:16:38 2017 Benoit Hamon
// Last update Mon Oct 02 16:17:36 2017 Benoit Hamon
//

#pragma once

#include <string>

namespace Base64 {
  std::string encrypt(const std::string &val);
  std::string decrypt(const std::string &val);
}
