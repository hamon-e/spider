//
// CryptServer.hpp for cpp_spider in sources/server
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 22:42:30 2017 Benoit Hamon
// Last update Tue Oct 10 17:50:38 2017 Benoit Hamon
//

#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/asio.hpp>
#include "ssl/CryptRSA.hpp"
#include "ssl/CryptAES.hpp"
#include "IDataBase.hpp"
#include "Packet.hpp"

class CryptServer {
  public:
    void init(IDataBase *db);

  public:
    void encrypt(Packet &packet);
    std::string encryptRSA(std::string const &cookie, std::string const &message);
    std::string encryptAES(std::string const &cookie, std::string const &message);

  public:
    void decrypt(Packet &packet);
    std::string decryptRSA(std::string const &encryptedMessage);
    std::string decryptAES(std::string const &cookie, std::string const &encryptedMessage);

  public:
    std::string initAES(std::string const &publicKey, std::string const &cookie);

  private:
    IDataBase *_db;
    CryptRSA _rsaServer;
};
