/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on April 11, 2014, 6:28 PM
 */

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/date.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


/*
 * 
 */

using namespace boost::posix_time;
using namespace boost::gregorian;
   
void set_year( uint64_t y, ptime& p) {
    tm pt_tm = to_tm( p);
    pt_tm.tm_year = y - 1900;
    p = ptime_from_tm( pt_tm);
}

int main(int argc, char** argv) {
   ptime t1( date(2002,Feb,10), hours(5)+minutes(4)+seconds(2)); 
   std::cout << to_simple_string( t1) << std::endl;
   set_year( 2001, t1);
   std::cout << to_simple_string( t1);
   
   return 0;
}

