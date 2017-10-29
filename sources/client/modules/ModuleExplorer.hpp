//
// Created by Benoit Hamon on 10/4/2017.
//

#pragma once

#include "../IModule.hpp"
#include "../IModuleCommunication.hpp"

class ModuleExplorer : public IModule {
  public:
    ModuleExplorer(IModuleCommunication *);

  public:
    void start() override;

  public:
    static boost::shared_ptr<ModuleExplorer> create(IModuleCommunication *);

  private:
    void changeDir(std::string const &path);
    std::vector<std::string> readDir();
    void sendFiles();

  private:
    IModuleCommunication *_moduleCommunication;
};
