//
// CryptClient.cpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 17:50:33 2017 Benoit Hamon
// Last update Sun Oct 29 12:09:47 2017 Benoit Hamon
//

#include <boost/filesystem.hpp>
#include "ssl/Base64.hpp"
#include "CryptClient.hpp"

#include <iostream>

void CryptClient::init() {
  if (!boost::filesystem::exists("./keys/aesiv.key")
      || !boost::filesystem::exists("./keys/aeskey.key")) {
    this->_rsaClient.genKey();
    this->_rsaServer.setKeyFromFile(ICryptAlgo::KeyType::RSA_PUB, "./keys/serverPubKey.key");

    this->_current = &this->_rsaServer;
    this->_currentType = "RSA";

    boost::property_tree::ptree ptree;
    ptree.add("type", "PublicKey");
    std::string key; this->_rsaClient.getKey(ICryptAlgo::KeyType::RSA_PUB, key);
    ptree.add("key", Base64::encrypt(key));
    this->_moduleCommunication->send(ptree);
  } else {
    this->_aes.setKeyFromFile(ICryptAlgo::KeyType::AES_KEY, "./keys/aeskey.key");
    this->_aes.setKeyFromFile(ICryptAlgo::KeyType::AES_IV, "./keys/aesiv.key");
    this->_current = &this->_aes;
    this->_currentType = "AES";
  }
}

void CryptClient::init(std::string const &aes_key, std::string const &aes_iv) {
  this->_aes.setKey(ICryptAlgo::KeyType::AES_KEY, Base64::decrypt(aes_key));
  this->_aes.setKey(ICryptAlgo::KeyType::AES_IV, Base64::decrypt(aes_iv));
  this->_aes.saveKeyInFile(ICryptAlgo::KeyType::AES_KEY, "./keys/aeskey.key");
  this->_aes.saveKeyInFile(ICryptAlgo::KeyType::AES_IV, "./keys/aesiv.key");
  this->_current = &this->_aes;
  this->_currentType = "AES";
}

void CryptClient::addModuleCommunication(IModuleCommunication *moduleCommunication) {
  this->_moduleCommunication = moduleCommunication;
}

void CryptClient::encrypt(Packet &packet) {
  std::string data = packet.get<Packet::Field::DATA, std::string>();

  std::cout << packet << std::endl;

  if (!data.empty()) {
    std::string res;

    this->_current->encrypt(data, res);

    packet.set(Packet::Field::DATA, Base64::encrypt(res));
    packet.set(Packet::Field::CRYPT, this->_currentType);
  }
}

std::string CryptClient::encryptMethod(Packet &packet) {
  return this->_currentType;
}

void CryptClient::decrypt(Packet &packet) {
  std::string data = packet.get<Packet::Field::DATA, std::string>();
  std::string crypt = packet.get<Packet::Field::CRYPT, std::string>();
  std::string res;

  std::cout << packet << std::endl;
  if (!data.empty()) {
    if (crypt == "AES")
      this->_aes.decrypt(Base64::decrypt(data), res);
    else if (crypt == "RSA") {
      this->_rsaClient.decrypt(Base64::decrypt(data), res);
    } else
      res = data;

    packet.set(Packet::Field::DATA, res);
  }
}
