//
// CryptAES.cpp for cpp_spider in sources/ssl
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Mon Oct 02 16:14:40 2017 Benoit Hamon
// Last update Tue Oct 10 18:35:15 2017 Benoit Hamon
//

#include <stdexcept>
#include <string.h>
#include <fstream>
#include "CryptAES.hpp"
#include "Base64.hpp"

CryptAES::CryptAES() {
  this->_aesEncryptContext = EVP_CIPHER_CTX_new();
  this->_aesDecryptContext = EVP_CIPHER_CTX_new();

  this->_aesKey = nullptr;
  this->_aesIv = nullptr;

  if (!this->_aesEncryptContext || !this->_aesDecryptContext)
    throw std::runtime_error("Could Not Initialize SSL");
}

CryptAES::~CryptAES() {
  EVP_CIPHER_CTX_free(this->_aesEncryptContext);
  EVP_CIPHER_CTX_free(this->_aesDecryptContext);

  ::free(this->_aesKey);
  ::free(this->_aesIv);
}

bool CryptAES::encrypt(std::string const &message, std::string &encryptedMessage) {
  size_t blockLength = 0;
  size_t encryptedMessageLength = 0;
  unsigned char *tmp;

  tmp = (unsigned char*)malloc(message.length() + AES_BLOCK_SIZE);
  if (!tmp)
    return false;

  if (!EVP_EncryptInit_ex(this->_aesEncryptContext, EVP_aes_256_cbc(), NULL,
                          this->_aesKey, this->_aesIv))
    return false;

  if (!EVP_EncryptUpdate(this->_aesEncryptContext, tmp, (int *)&blockLength,
                         (unsigned char *)message.c_str(), message.length()))
    return false;

  encryptedMessageLength += blockLength;
  if (!EVP_EncryptFinal_ex(this->_aesEncryptContext, tmp + encryptedMessageLength,
                           (int *)&blockLength))
    return false;
  encryptedMessageLength += blockLength;

  encryptedMessage.assign((char *)tmp, encryptedMessageLength);
  ::free(tmp);
  return true;
}

bool CryptAES::decrypt(std::string const &encryptedMessage, std::string &message) {
  size_t messageLength = 0;
  size_t blockLength = 0;
  unsigned char *tmp;

  tmp = (unsigned char*)malloc(encryptedMessage.length());
  if (!tmp)
    return false;

  if (!EVP_DecryptInit_ex(this->_aesDecryptContext, EVP_aes_256_cbc(), NULL,
                          this->_aesKey, this->_aesIv))
    return false;

  if (!EVP_DecryptUpdate(this->_aesDecryptContext, tmp, (int*)&blockLength,
                         (unsigned char *)encryptedMessage.c_str(), encryptedMessage.length()))
    return false;
  messageLength += blockLength;

  if (!EVP_DecryptFinal_ex(this->_aesDecryptContext, tmp + messageLength, (int*)&blockLength))
    return false;
  messageLength += blockLength;

  message.assign(tmp, tmp + messageLength);
  ::free(tmp);
  return true;
}

bool CryptAES::genKey() {
  this->_aesKey = (unsigned char *)malloc(AES_KEYLEN / 8);
  this->_aesIv = (unsigned char *)malloc(AES_KEYLEN / 8);

  if (this->_aesKey == NULL || this->_aesIv == NULL)
    return false;

  if (!RAND_bytes(this->_aesKey, AES_KEYLEN / 8) || !RAND_bytes(this->_aesIv, AES_KEYLEN / 8))
    return false;

  return true;
}

bool CryptAES::getKey(KeyType type, std::string &key) {
  unsigned char *store = type == AES_IV ? this->_aesIv : this->_aesKey;
  std::string tmp;

  if (!store)
    return false;
  tmp.assign(store, store + AES_KEYLEN / 8);
  key.assign(Base64::encrypt(tmp));
  return true;
}

bool CryptAES::setKey(KeyType type, std::string const &key) {
  unsigned char **store = type == AES_IV ? &this->_aesIv : &this->_aesKey;

  *store = (unsigned char *)strndup(Base64::decrypt(key).c_str(), AES_KEYLEN / 8);
  if (!*store)
    return false;
  return true;
}

bool CryptAES::saveKeyInFile(KeyType type, std::string const &filename) {
  std::string tmp;
  if (type == AES_IV) {
    if (!this->_aesIv)
      return false;
    tmp.assign(this->_aesIv, this->_aesIv + AES_KEYLEN / 8);
  }
  else {
    if (!this->_aesKey)
      return false;
    tmp.assign(this->_aesKey, this->_aesKey + AES_KEYLEN / 8);
  }

  try {
    std::ofstream file(filename);
    file << Base64::encrypt(tmp);
    file.close();
  } catch (std::exception) {
    return false;
  }

  return true;
}

bool CryptAES::setKeyFromFile(KeyType type, std::string const &filename) {
  std::string tmp;

  try {
    std::ifstream file(filename);
    file >> tmp;
    file.close();
  } catch (std::exception) {
    return false;
  }

  tmp = Base64::decrypt(tmp);
  if (type == AES_IV)
    this->_aesIv = (unsigned char *)strndup(tmp.c_str(), AES_KEYLEN / 8);
  else
    this->_aesKey = (unsigned char *)strndup(tmp.c_str(), AES_KEYLEN / 8);
  return true;
}
