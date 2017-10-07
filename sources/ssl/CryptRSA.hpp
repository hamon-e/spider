//
// CryptRSA.hpp for cpp_spider in sources/ssl
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Mon Oct 02 16:13:38 2017 Benoit Hamon
// Last update Thu Oct 05 22:04:51 2017 Benoit Hamon
//

#pragma once

#include "ICrypt.hpp"

#define RSA_KEYLEN 2048

class CryptRSA : public ICrypt {
  public:
    CryptRSA();
    ~CryptRSA();

  public:
    bool genKey() override;
    bool setKey(KeyType type, std::string const &key) override;
    bool getKey(KeyType type, std::string &key) override;

  public:
    bool encrypt(std::string const &message, std::string &encryptedMessage) override;
    bool decrypt(std::string const &encryptedMessage, std::string &message) override;

  public:
    bool setKeyFromFile(KeyType type, std::string const &filename) override;
    bool saveKeyInFile(KeyType type, std::string const &filename) override;

  private:
    RSA *_publicKey;
    RSA *_privateKey;
};
