//
// CryptRSA.hpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Mon Oct 02 16:13:38 2017 Benoit Hamon
// Last update Mon Oct 02 19:18:38 2017 Benoit Hamon
//

#pragma once

#include "ICrypt.hpp"

#define RSA_KEYLEN 2048

class CryptRSA : public ICrypt {
  public:
    CryptRSA();
    ~CryptRSA();

  public:
    virtual bool genKey();
    virtual bool setKey(KeyType type, std::string const &key);
    virtual bool getKey(KeyType type, std::string &key);
    virtual bool encrypt(std::string const &message, std::string &encryptedMessage);
    virtual bool decrypt(std::string const &encryptedMessage, std::string &message);

  public:
    bool setKeyFromFile(KeyType type, std::string const &filename);
    bool saveKeyInFile(KeyType type, std::string const &filename);

  private:
    RSA *_publicKey;
    RSA *_privateKey;
};
