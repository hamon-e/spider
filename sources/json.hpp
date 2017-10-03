#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace json {
    std::string stringify(boost::property_tree::ptree const &ptree, bool pretty = false);
}
