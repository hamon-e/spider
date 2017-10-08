//
// ServerCrypt.hpp for cpp_spider in sources/server
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Sun Oct 08 22:42:30 2017 Benoit Hamon
// Last update Sun Oct 08 23:36:36 2017 Benoit Hamon
//

#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/asio.hpp>
#include "ssl/ICryptAlgo.hpp"
#include "IDataBase.hpp"

class ServerCrypt {
  public:
    void init(IDataBase *db);

  public:
    std::string decryptRSA(std::string const &encryptedMessage);
    std::string encryptRSA(std::string const &cookie, std::string const &encryptedMessage);
    std::string encrypt(std::string const &cookie, std::string const &message);
    std::string decrypt(std::string const &cookie, std::string const &message);

  public:
    std::string initClient(boost::property_tree::ptree const &ptree);
};
