#include <boost/property_tree/ptree.hpp>

class IDataBase {
public:
  void insert(boost::property_tree const &doc);
  boost::property_tree const &find(boost::property_tree const &query);
  void update(boost::property_tree const &query, boost::property_tree const &update);
  void remove(boost::property_tree const &query);
};
