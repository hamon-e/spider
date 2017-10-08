//
// CryptClient.hpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 17:52:53 2017 Benoit Hamon
// Last update Sun Oct 08 22:43:57 2017 Benoit Hamon
//

#pragma once

#include "IModuleCommunication.hpp"
#include "ssl/CryptRSA.hpp"
#include "ssl/CryptAES.hpp"

class CryptClient {
  public:
    std::string encrypt(std::string const &message);
    std::string decrypt(std::string const &encryptedMessage);

  public:
    void init();
    void init(boost::property_tree::ptree const &ptree);
    void addModuleCommunication(IModuleCommunication *moduleCommunication);

  private:
    IModuleCommunication *_moduleCommunication;
    ICryptAlgo *_current;
    CryptRSA _rsaClient;
    CryptRSA _rsaServer;
    CryptAES _aes;
};
