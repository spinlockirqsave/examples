/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on October 3, 2013, 1:48 AM
 */

#include <iostream>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    typedef boost::unordered_map<std::string, int> NumbersMap;
    NumbersMap numbers;
    numbers["1"]=1;
    numbers["2"]=2;
    numbers["13"]=13;
    numbers["100"]=100;
    
    BOOST_FOREACH(NumbersMap::value_type i, numbers) {
      std::cout<<i.first<<","<<i.second<<"\n";
    }
    return 0;
}

