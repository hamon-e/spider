//
// CryptRSA.cpp for cpp_spider in sources/ssl
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Mon Oct 02 16:14:55 2017 Benoit Hamon
// Last update Wed Oct 11 00:22:31 2017 Benoit Hamon
//

#include "CryptRSA.hpp"

CryptRSA::CryptRSA() {
  this->_publicKey = nullptr;
  this->_privateKey = nullptr;
}

CryptRSA::~CryptRSA() {
  RSA_free(this->_publicKey);
  if (this->_publicKey != this->_privateKey)
    RSA_free(this->_privateKey);
}

bool CryptRSA::setKey(KeyType type, std::string const &key) {
  BIO *bio = BIO_new_mem_buf(key.c_str(), key.length());
  if (!bio)
    return false;

  EVP_PKEY *tmp;
  if (type == RSA_PUB)
    tmp = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
  else
    tmp = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
  if (!tmp)
    return false;

  RSA **store = type == RSA_PUB ? &this->_publicKey : &this->_privateKey;
  *store = EVP_PKEY_get1_RSA(tmp);
  if (!*store)
    return false;
  return true;
}

bool CryptRSA::getKey(KeyType type, std::string &key) {
  BIO *bio= BIO_new(BIO_s_mem());
  if (!bio)
    return false;

  if (type == RSA_PUB)
    PEM_write_bio_RSA_PUBKEY(bio, this->_publicKey);
  else
    PEM_write_bio_RSAPrivateKey(bio, this->_privateKey, NULL, NULL, 0, NULL, NULL);

  int len = BIO_pending(bio);
  char *tmp = (char *)malloc(sizeof(char) * len);

  BIO_read(bio, tmp, len);
  key.assign(tmp, len);
  return true;
}

#include <string.h>
#include <iostream>
bool CryptRSA::encrypt(std::string const &message, std::string &encryptedMessage) {
  unsigned char *tmp = (unsigned char *)malloc(RSA_size(this->_publicKey));
  int encryptMessageLength = 0;
  if (!tmp)
    return false;

  encryptMessageLength = RSA_public_encrypt(message.length(), (unsigned char *)message.c_str(),
                                            tmp, this->_publicKey, RSA_PKCS1_OAEP_PADDING);
  if (encryptMessageLength == -1)
    return false;

  encryptedMessage.assign(tmp, tmp + encryptMessageLength);
  ::free(tmp);
  return true;
}

bool CryptRSA::decrypt(std::string const &encryptedMessage, std::string &message) {
  unsigned char *tmp = (unsigned char *)malloc(encryptedMessage.length());
  int messageLenght = 0;

  if (!tmp)
    return false;

  messageLenght = RSA_private_decrypt(encryptedMessage.length(),
                                      (unsigned char *)encryptedMessage.c_str(), tmp,
                                      this->_privateKey, RSA_PKCS1_OAEP_PADDING);
  if (messageLenght == -1)
    return false;

  message.assign(tmp, tmp + messageLenght);
  ::free(tmp);
  return true;
}

bool CryptRSA::genKey() {
  this->_publicKey = RSA_new();
  BIGNUM *bn = BN_new();

  if (!this->_publicKey || !bn)
    goto err;

  if (BN_set_word(bn, RSA_F4) == -1)
    goto err;

  if (!RSA_generate_key_ex(this->_publicKey, RSA_KEYLEN, bn, NULL))
    goto err;

  this->_privateKey = this->_publicKey;
  return true;

  err:
  RSA_free(this->_publicKey);
  BN_free(bn);
  this->_publicKey = NULL;
  return false;
}

bool CryptRSA::setKeyFromFile(KeyType type, std::string const &filename) {
  FILE *fp = ::fopen(filename.c_str(), "r");
  if (fp == (void *)-1)
    return false;

  RSA **store;
  if (type == RSA_PUB) {
    store = &this->_publicKey;
    *store = PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL);
  } else {
    store = &this->_privateKey;
    *store = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
  }
  ::fclose(fp);
  if (!*store)
    return false;
  return true;
}

bool CryptRSA::saveKeyInFile(KeyType type, std::string const &filename) {
  FILE *fp = fopen(filename.c_str(), "wt");
  if (fp == (void *)-1)
    return false;

  if (type == RSA_PUB)
    PEM_write_RSA_PUBKEY(fp, this->_publicKey);
  else
    PEM_write_RSAPrivateKey(fp, this->_privateKey, NULL, NULL, 0, NULL, NULL);
  ::fclose(fp);
  return true;
}
