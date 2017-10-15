//
// CryptClient.hpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 17:52:53 2017 Benoit Hamon
// Last update Wed Oct 11 01:01:18 2017 Benoit Hamon
//

#pragma once

#include "IModuleCommunication.hpp"
#include "ssl/CryptRSA.hpp"
#include "ssl/CryptAES.hpp"
#include "Packet.hpp"

class CryptClient {
  public:
    void encrypt(Packet &packet);
    std::string encryptMethod(Packet &packet);
    void decrypt(Packet &packet);

  public:
    void init();
    void init(std::string const &aes_key, std::string const &aes_iv);
    void addModuleCommunication(IModuleCommunication *moduleCommunication);

  private:
    IModuleCommunication *_moduleCommunication;
    ICryptAlgo *_current;
    std::string _currentType;
    CryptRSA _rsaClient;
    CryptRSA _rsaServer;
    CryptAES _aes;
};
