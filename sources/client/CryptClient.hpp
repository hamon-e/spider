//
// CryptClient.hpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 17:52:53 2017 Benoit Hamon
// Last update Sun Oct 08 18:15:15 2017 Benoit Hamon
//

#pragma once

#include "ICrypt.hpp"
#include "IModuleCommunication.hpp"
#include "ssl/CryptRSA.hpp"
#include "ssl/CryptAES.hpp"

class CryptClient : public ICrypt {
  public:
    CryptClient(IModuleCommunication *moduleCommunication);

  public:
    std::string encrypt(std::string const &message) override;
    std::string decrypt(std::string const &encryptedMessage) override;

  public:
    void init();
    void init(boost::property_tree::ptree const &ptree);

  private:
    IModuleCommunication *_moduleCommunication;
    ICryptAlgo *_current;
    CryptRSA _rsaClient;
    CryptRSA _rsaServer;
    CryptAES _aes;
};
