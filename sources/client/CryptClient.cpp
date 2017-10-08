//
// CryptClient.cpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 17:50:33 2017 Benoit Hamon
// Last update Sun Oct 08 19:37:43 2017 Benoit Hamon
//

#include <boost/filesystem.hpp>
#include "Base64.hpp"
#include "CryptClient.hpp"

void CryptClient::init() {
  if (!boost::filesystem::exists("aesiv.key") || !boost::filesystem::exists("aeskey.key")) {
    this->_rsaClient.genKey();
    this->_rsaServer.setKeyFromFile(ICryptAlgo::KeyType::RSA_PUB, "serverPubKey.key");

    this->_current = &this->_rsaServer;

    boost::property_tree::ptree ptree;
    ptree.add("type", "PublicKey");
    std::string key; this->_rsaClient.getKey(ICryptAlgo::KeyType::RSA_PUB, key);
    ptree.add("key", Base64::encrypt(key));
    this->_moduleCommunication->send(ptree);
  } else {
    this->_aes.setKeyFromFile(ICryptAlgo::KeyType::AES_KEY, "aeskey.key");
    this->_aes.setKeyFromFile(ICryptAlgo::KeyType::AES_IV, "aesiv.key");
    this->_current = &this->_aes;
  }
}

void CryptClient::init(boost::property_tree::ptree const &ptree) {
  this->_aes.setKey(ICryptAlgo::KeyType::AES_KEY,
		    Base64::decrypt(ptree.get<std::string>("AES_KEY")));
  this->_aes.setKey(ICryptAlgo::KeyType::AES_IV,
		    Base64::decrypt(ptree.get<std::string>("AES_IV")));
  this->_current = &this->_aes;
}

void CryptClient::addModuleCommunication(IModuleCommunication *moduleCommunication) {
  this->_moduleCommunication = moduleCommunication;
}

std::string CryptClient::encrypt(std::string const &message) {
  std::string res;

  this->_current->encrypt(message, res);
  return Base64::encrypt(res);
}

std::string CryptClient::decrypt(std::string const &encryptedMessage) {
  std::string res;

  this->_current->decrypt(Base64::decrypt(encryptedMessage), res);
  return res;
}
