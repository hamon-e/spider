//
// CryptServer.cpp for cpp_spider in sources/server
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 22:42:24 2017 Benoit Hamon
// Last update Wed Oct 11 23:51:19 2017 Benoit Hamon
//

#include "ssl/ICryptAlgo.hpp"
#include "ssl/Base64.hpp"
#include "json.hpp"
#include "CryptServer.hpp"

#include <iostream>
void CryptServer::init(IDataBase *db) {
  this->_db = db;
  this->_rsaServer.setKeyFromFile(ICryptAlgo::KeyType::RSA_PRIV, "./serverPrivKey.key");
}

std::string CryptServer::encryptRSA(std::string const &cookie, std::string const &message) {
  CryptRSA rsaClient;
  boost::property_tree::ptree ptree;
  boost::property_tree::ptree query;

  query.put("cookie", cookie);
  ptree = this->_db->findOne("keys", query);
  rsaClient.setKey(ICryptAlgo::KeyType::RSA_PUB, ptree.get<std::string>("pubkey"));

  std::string encryptedMessage;
  rsaClient.encrypt(message, encryptedMessage);

  return Base64::encrypt(encryptedMessage);
}

std::string CryptServer::encryptAES(std::string const &cookie, std::string const &message) {
  CryptAES aes;
  boost::property_tree::ptree ptree;
  boost::property_tree::ptree query;

  query.put("cookie", cookie);
  ptree = this->_db->findOne("keys", query);
  aes.setKey(ICryptAlgo::KeyType::AES_KEY, Base64::decrypt(ptree.get<std::string>("AES_KEY")));
  aes.setKey(ICryptAlgo::KeyType::AES_IV, Base64::decrypt(ptree.get<std::string>("AES_IV")));

  std::string encryptedMessage;
  aes.encrypt(message, encryptedMessage);

  return Base64::encrypt(encryptedMessage);
}

void CryptServer::encrypt(Packet &packet, std::string const &host, std::string const &port) {
  std::string data = packet.get<Packet::Field::DATA, std::string>();
  std::string cookie;

  boost::property_tree::ptree query;
  query.put("host", host);
  query.put("port", port);
  query = this->_db->findOne("client", query);

  cookie = query.get("cookie", "");

  if (!data.empty()) {
    std::string crypt;
    boost::property_tree::ptree query;
    boost::property_tree::ptree ptree;
    query.put("cookie", cookie);
    try {
      ptree = this->_db->findOne("keys", query);
      crypt = ptree.get<std::string>("sent") == "0" ? "RSA" : "AES";
    } catch (std::exception &) {
      crypt = "NONE";
    }

    std::string message;
    if (crypt == "RSA")
      message = this->encryptRSA(cookie, data);
    else if (crypt == "AES")
      message = this->encryptAES(cookie, data);
    else
      message = data;
    packet.set(Packet::Field::DATA, message);
    packet.set(Packet::Field::CRYPT, crypt);
  }
}

std::string CryptServer::encryptMethod(Packet &packet, std::string const &host, std::string const &port) {
  std::string crypt;

  std::string cookie;
  boost::property_tree::ptree query;
  query.put("host", host);
  query.put("port", port);
  query = this->_db->findOne("client", query);
  cookie = query.get("cookie", "");

  boost::property_tree::ptree ptree;
  boost::property_tree::ptree query2;
  query2.put("cookie", cookie);
  try {
    ptree = this->_db->findOne("keys", query2);
    crypt = ptree.get<std::string>("sent") == "0" ? "RSA" : "AES";
  } catch (std::exception &) {
    crypt = "NONE";
  }

  return crypt;
}

std::string CryptServer::decryptAES(std::string const &cookie, std::string const &encryptedMessage) {
  CryptAES aes;
  boost::property_tree::ptree ptree;
  boost::property_tree::ptree query;

  query.put("cookie", cookie);
  ptree = this->_db->findOne("keys", query);
  ptree.put("sent", "1");
  this->_db->update("keys", query, ptree);

  aes.setKey(ICryptAlgo::KeyType::AES_KEY, Base64::decrypt(ptree.get<std::string>("AES_KEY")));
  aes.setKey(ICryptAlgo::KeyType::AES_IV, Base64::decrypt(ptree.get<std::string>("AES_IV")));

  std::string message;
  aes.decrypt(Base64::decrypt(encryptedMessage), message);
  return message;
}

std::string CryptServer::decryptRSA(std::string const &encryptedMessage) {
  std::string message;

  this->_rsaServer.decrypt(Base64::decrypt(encryptedMessage), message);
  return message;
}

void CryptServer::decrypt(Packet &packet) {
  std::string data = packet.get<Packet::Field::DATA, std::string>();

  if (!data.empty()) {
    std::string crypt = packet.get<Packet::Field::CRYPT, std::string>();
    std::string cookie = packet.get<Packet::Field::COOKIE, std::string>();

    std::string message;
    if (crypt == "RSA")
      message = this->decryptRSA(data);
    else if (crypt == "AES")
      message = this->decryptAES(cookie, data);

    packet.set(Packet::Field::DATA, message);
    std::cout << "RECEIV" << std::endl;
    std::cout << packet << std::endl;
    std::cout << std::endl;
  }
}

std::string CryptServer::genCookie(std::string const &cookie) {
  boost::property_tree::ptree query;
  boost::property_tree::ptree ptree;
  std::string nCookie = "012345";

  query.put("cookie", cookie);
  ptree = this->_db->findOne("client", query);
  ptree.put("cookie", nCookie);
  std::cout << query << std::endl;
  std::cout << ptree << std::endl;
  this->_db->update("client", query, ptree);
  return nCookie;
}

std::string CryptServer::initAES(std::string const &publicKey, std::string &cookie) {
  CryptAES aes;
  boost::property_tree::ptree ptree;
  std::string key;
  std::string keyiv;

  cookie = this->genCookie(cookie);

  aes.genKey();

  ptree.put("cookie", cookie);
  ptree.put("sent", "0");
  ptree.put("pubkey", publicKey);

  aes.getKey(ICryptAlgo::KeyType::AES_KEY, key);
  ptree.put("AES_KEY", Base64::encrypt(key));

  aes.getKey(ICryptAlgo::KeyType::AES_IV, keyiv);
  ptree.put("AES_IV", Base64::encrypt(keyiv));

  this->_db->insert("keys", ptree);

  boost::property_tree::ptree send;
  send.put("type", "AesKey");

  boost::property_tree::ptree child;
  child.put("cookie", cookie);
  child.put("AES_KEY", Base64::encrypt(key));
  child.put("AES_IV", Base64::encrypt(keyiv));

  send.add_child("key", child);

  return json::stringify(send);
}
