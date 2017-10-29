#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace json {
  std::string stringify(boost::property_tree::ptree const &ptree, bool pretty = false);
  boost::property_tree::ptree parse(std::string const &data);
  boost::property_tree::ptree parse(std::vector<boost::property_tree::ptree> const &vec);
}
