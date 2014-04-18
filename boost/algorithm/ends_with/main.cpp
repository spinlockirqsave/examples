/* 
 * File:   main.cpp
 * Author: piter
 *
 * Created on April 18, 2014, 5:58 PM
 */

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/date.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
/*
 * 
 */


int main(int argc, char** argv) {

   std::string s = "somet0hing";
   std::string::iterator it = s.begin();
   bool b = 0;
   b = boost::algorithm::ends_with( &s[0], "g");
   std::cout << b;
   b = boost::algorithm::ends_with( &(*it), "g");
   std::cout << b;
   b = boost::algorithm::ends_with( boost::make_iterator_range( it, s.end()), "g");
   std::cout << b;
   
   return 0;
}
