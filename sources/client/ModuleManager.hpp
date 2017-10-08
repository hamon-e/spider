//
// Created by Benoit Hamon on 10/4/2017.
//

#pragma once

#include <boost/function.hpp>
#include <boost/thread/thread.hpp>

#include "IModule.hpp"
#include "IModuleCommunication.hpp"

typedef boost::shared_ptr<IModule> (module_t)(IModuleCommunication *);

class ModuleManager {
public:
    ModuleManager(IModuleCommunication *moduleCommunication = nullptr,
		  std::string const &dirname = ".");
    ~ModuleManager();

public:
    void run();
    void addModuleCommunication(IModuleCommunication *moduleCommunication);
    void addLibrary(boost::property_tree::ptree const &ptree);

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
    IModuleCommunication *_moduleCommunication;
};
