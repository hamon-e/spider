//
// Created by golitij on 04/10/17.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
using ptree = boost::property_tree::ptree;


std::string  my_iter(ptree const &pt, std::string path)
{
    //std::string path;

    for(boost::property_tree::ptree::const_iterator iter = pt.begin(); iter != pt.end(); iter++)
    {
        if (!iter->second.empty())
        {
            std::cout << path << ":=> "<< iter->first << ":{" << std::endl;
            if (path != iter->first)
                path = path + "." + iter->first;

            path = my_iter(iter->second, path);
            std::cout << "}" << std::endl;
        }
        else {
            std::cout << iter->first << " :=> " << iter->second.data() << std::endl;
            if (iter->first == "")
                std::cout << "first vide" << std::endl;
        }
    }
    return (path);
}

int main()
{
    std::string ret;
    ptree pt;
    read_json("./myjson.json",pt);

   ret = my_iter(pt,pt.begin()->first);
    std::cout << "path le plus long = " << ret << std::endl;
}