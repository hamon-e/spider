//
// CryptAES.hpp for cpp_spider in sources/ssl
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Mon Oct 02 16:14:04 2017 Benoit Hamon
// Last update Thu Oct 05 22:06:50 2017 Benoit Hamon
//

#pragma once

#include "ICrypt.hpp"

#define AES_KEYLEN 256

class CryptAES : public ICrypt {
  public:
    CryptAES();
    ~CryptAES();

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
    EVP_CIPHER_CTX *_aesEncryptContext;
    EVP_CIPHER_CTX *_aesDecryptContext;

  private:
    unsigned char *_aesKey;
    unsigned char *_aesIv;
};
