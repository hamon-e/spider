#include <boost/property_tree/ptree.hpp>

class IDocument {
public:
    template<typename T>
    T get(std::string const &field) const;
    template<typename T>
    T get(std::string const &field, T const &default_value) const;

    IDocument &put(std::string const &field, T const value);
};

class IDataBase {
public:
    typedef boost::property_tree::ptree ptree

    virtual void insert(ptree const &doc) = 0;
    virtual IDocument const &find(ptree const &query) = 0;
    virtual void update(ptree const &query, ptree const &update) = 0;
    virtual void remove(ptree const &query) = 0;
};
