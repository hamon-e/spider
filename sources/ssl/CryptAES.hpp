//
// CryptAES.hpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Mon Oct 02 16:14:04 2017 Benoit Hamon
// Last update Mon Oct 02 19:22:52 2017 Benoit Hamon
//

#pragma once

#include "ICrypt.hpp"

#define AES_KEYLEN 256

class CryptAES : public ICrypt {
  public:
    CryptAES();
    ~CryptAES();

  public:
    virtual bool genKey();
    virtual bool setKey(KeyType type, std::string const &key);
    virtual bool getKey(KeyType type, std::string &key);
    virtual bool encrypt(std::string const &message, std::string &encryptedMessage);
    virtual bool decrypt(std::string const &encryptedMessage, std::string &message);

  private:
    EVP_CIPHER_CTX *_aesEncryptContext;
    EVP_CIPHER_CTX *_aesDecryptContext;

  private:
    unsigned char *_aesKey;
    unsigned char *_aesIv;
};
