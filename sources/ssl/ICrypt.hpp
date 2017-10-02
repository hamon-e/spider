//
// ICrypt.hpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Mon Oct 02 16:12:55 2017 Benoit Hamon
// Last update Mon Oct 02 19:07:57 2017 Benoit Hamon
//

#pragma once

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <string>

class ICrypt {
  public:
    enum KeyType {
      AES_IV,
      AES_KEY,
      RSA_PUB,
      RSA_PRIV
    };

  public:
    virtual bool genKey() = 0;
    virtual bool setKey(KeyType type, std::string const &key) = 0;
    virtual bool getKey(KeyType type, std::string &key) = 0;
    virtual bool encrypt(std::string const &message, std::string &encryptedMessage) = 0;
    virtual bool decrypt(std::string const &encryptedMessage, std::string &message) = 0;
};
