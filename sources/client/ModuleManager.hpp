//
// Created by Benoit Hamon on 10/4/2017.
//

#pragma once

#include <boost/function.hpp>
#include <boost/thread/thread.hpp>

#include "IModule.hpp"
#include "ModuleCommunication.hpp"
#include "Client.hpp"

typedef boost::shared_ptr<IModule> (module_t)(ModuleCommunication *);

class ModuleManager {
public:
    ModuleManager(Client &_client, std::string const &dirname = ".");
    ~ModuleManager();

public:
    void run();

private:
    struct Library {
        std::string name;
        boost::shared_ptr<IModule> module;
        boost::function<module_t> creator;
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
