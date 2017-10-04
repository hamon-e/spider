//
// main.cpp for cpp_spider in sources/client
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Wed Oct 04 18:03:49 2017 Benoit Hamon
// Last update Wed Oct 04 20:07:50 2017 Benoit Hamon
//

#include <iostream>
#include <regex>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/thread/thread.hpp>

#include "IModule.hpp"

typedef boost::shared_ptr<IModule> (module_t)();

class ModuleManager {
  public:
    ModuleManager(std::string const &dirname = ".");
    ~ModuleManager();

  public:
    void run();

  private:
    struct Library {
      std::string name;
      boost::shared_ptr<IModule> module;
    };

  private:
    void runLibraries();
    void runLibrary(std::string const &libraryName);
    std::vector<std::string> readDirectory();

  private:
    std::string _dirname;
    std::vector<Library> _libraries;
    boost::thread_group _threads;
    ModuleCommunication _moduleCommunication;
};


ModuleManager::ModuleManager(std::string const &dirname) : _dirname(dirname) {}

ModuleManager::~ModuleManager() {}

std::vector<std::string> ModuleManager::readDirectory() {
  boost::filesystem::path p(this->_dirname);
  std::vector<std::string> res;
  std::regex regex(".+\\.dll");

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
    boost::shared_ptr<IModule> plugin = creator();
    this->_threads.create_thread(boost::bind(&IModule::start, plugin.get(), this->_moduleCommunication));
    this->_libraries.push_back({libraryName, plugin});
  } catch (std::exception) {
    this->_libraries.push_back({libraryName, nullptr});
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
    sleep(1);
  }
  this->_threads.join_all();
}

int main() {
  ModuleManager mod("../");
  mod.run();
  return 0;
}
