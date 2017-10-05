//
// Created by Benoit Hamon on 10/3/2017.
//

#include <iostream>
#include <boost/dll/alias.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include "ModuleExplorer.hpp"

void ModuleExplorer::start(ModuleCommunication &com) {
  ModuleCommunication::Order order;

  while (true) {
    if (com.get("Explorer", order)) {
      if (order.name == "chdir")
	this->changeDir(order.value);
      else if (order.name == "readdir")
	this->sendFiles();
    }
  }
}

boost::shared_ptr<ModuleExplorer> ModuleExplorer::create() {
    return boost::shared_ptr<ModuleExplorer>(
            new ModuleExplorer()
    );
}

void ModuleExplorer::changeDir(std::string const &path) {
  boost::filesystem::current_path(path);
}

std::vector<std::string> ModuleExplorer::readDir() {
  boost::filesystem::path p(".");
  std::vector<std::string> res;

  if (is_directory(p)) {
    for (auto &entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {})) {
      res.push_back(entry.path().string());
    }
  }
  return res;
}

void ModuleExplorer::sendFiles() {
  auto files = this->readDir();

  for (auto &elem : files) {
    std::cout << elem << std::endl;
  }
}

BOOST_DLL_ALIAS(ModuleExplorer::create, create_module)
