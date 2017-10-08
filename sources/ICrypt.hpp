//
// ICrypt.hpp for cpp_spider in sources
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 17:45:50 2017 Benoit Hamon
// Last update Sun Oct 08 19:43:37 2017 Benoit Hamon
//

#pragma once

#include "ssl/ICryptAlgo.hpp"

class ICrypt {
  public:
    virtual std::string encrypt(std::string const &message) = 0;
    virtual std::string decrypt(std::string const &encryptedMessage) = 0;
};
