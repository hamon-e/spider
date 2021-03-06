//
// Created by Benoit Hamon on 10/4/2017.
//

#include <iostream>
#include <fstream>
#include <regex>
#include <exception>
#include <boost/dll/import.hpp>
#include <boost/range/iterator_range.hpp>

#include "ModuleManager.hpp"
#include "ssl/Base64.hpp"

ModuleManager::ModuleManager(IModuleCommunication *moduleCommunication,
                             std::string const &dirname)
        : _dirname(dirname), _moduleCommunication(moduleCommunication) {}

ModuleManager::~ModuleManager() {}

std::vector<std::string> ModuleManager::readDirectory() {
  boost::filesystem::path p(this->_dirname);
  std::vector<std::string> res;
  std::regex regex(".+\\.so");

  if (is_directory(p)) {
    for (auto &entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {})) {
      std::string tmp(entry.path().string());
      if (std::regex_match(tmp, regex))
        res.push_back(tmp);
    }
  }
  return res;
}

void ModuleManager::runLibrary(std::string const &libraryName) {
  boost::filesystem::path shared_library_path(libraryName);
  boost::function<module_t > creator;

  std::cout << libraryName << std::endl;
  try {
    creator = boost::dll::import_alias<module_t>(shared_library_path, "create_module");
    boost::shared_ptr<IModule> plugin = creator(this->_moduleCommunication);
    this->_threads.create_thread(boost::bind(&IModule::start, plugin.get()));
    this->_libraries.push_back({libraryName, plugin, creator});
  } catch (std::exception) {
    this->_libraries.push_back({libraryName, nullptr, creator});
  }
}

void ModuleManager::runLibraries() {
  std::vector<std::string> librariesNames = this->readDirectory();

  for (auto &libraryName : librariesNames) {
    if (std::find_if(this->_libraries.begin(),
                     this->_libraries.end(),
                     [libraryName](Library &lib) {return lib.name == libraryName;}) == this->_libraries.end()) {
      runLibrary(libraryName);
    }
  }
}

void ModuleManager::run() {
  while (true) {
    this->runLibraries();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
  }
  this->_threads.join_all();
}

void ModuleManager::addModuleCommunication(IModuleCommunication *moduleCommunication) {
  this->_moduleCommunication = moduleCommunication;
}

void ModuleManager::addLibrary(boost::property_tree::ptree const &ptree) {
  try {
    std::ofstream file(this->_dirname
                       + ptree.get<std::string>("filename"));

    file << Base64::decrypt(ptree.get<std::string>("data"));
    file.close();
  } catch (std::exception) {}
}
