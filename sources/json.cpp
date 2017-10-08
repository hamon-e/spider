#include "json.hpp"

std::string json::stringify(boost::property_tree::ptree const &ptree, bool pretty) {
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, ptree, pretty);
    return ss.str();
}

boost::property_tree::ptree json::parse(std::string const &data) {
    boost::property_tree::ptree ptree;
    std::stringstream ss;
    ss << data;
    boost::property_tree::json_parser::read_json(ss, ptree);
    return ptree;
}
