/* 
 * File:   main.cpp
 * Author: postmaster cf16.eu
 *
 * Created on October 4, 2013, 5:29 AM
 */

#include <iostream>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/predicate.hpp>
using namespace std;

/*
 * 
 */
struct iequal_to
    : std::binary_function<std::string, std::string, bool>
{
    bool operator()(std::string const& x,
        std::string const& y) const
    {
        return boost::algorithm::iequals(x, y, std::locale());
    }
};

struct ihash
    : std::unary_function<std::string, std::size_t>
{
    std::size_t operator()(std::string const& x) const
    {
        std::size_t seed = 0;
        std::locale locale;

        for(std::string::const_iterator it = x.begin();
            it != x.end(); ++it)
        {
            boost::hash_combine(seed, std::toupper(*it, locale));
        }

        return seed;
    }
};

int main(int argc, char** argv) {

    typedef boost::unordered_map<std::string, int, ihash, iequal_to> idictionary;
    
    idictionary dict;
    dict["1"]=1;
    dict["2"]=2;
    dict["13"]=13;
    dict["100"]=100;
    
    // since the elements aren't ordered, the output of
    // following can be in any order
    BOOST_FOREACH(idictionary::value_type i, dict) {
      std::cout<<i.first<<","<<i.second<<"\n";
    }
    return 0;
}

