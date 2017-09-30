#include <boost/property_tree/ptree.hpp>

class IDataBase {
public:
    using ptree = boost::property_tree::ptree;

    virtual void insert(ptree const &doc) = 0;
    virtual ptree const &find(ptree const &query) = 0;
    virtual void update(ptree const &query, ptree const &update) = 0;
    virtual void remove(ptree const &query) = 0;
};
