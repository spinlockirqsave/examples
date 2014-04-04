/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 2, 2013, 10:22 PM
 */

#include <cstdlib>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
//using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    boost::gregorian::date d1(2013,boost::gregorian::Jan,31);
    boost::gregorian::date d2(2013,boost::gregorian::Feb,28);
    boost::gregorian::date d3(2013,boost::gregorian::Mar,31);
    
    std::vector<boost::gregorian::date > v;
    v.push_back(d1);
    v.push_back(d2);
    v.push_back(d3);
    
    boost::gregorian::date_duration duration(1);
    
    for(std::vector<boost::gregorian::date >::iterator it=v.begin();it!=v.end();it++){
        *it+=duration;
        std::cout << *it <<" "<< (*it).day_of_week() << std::endl;
    }
    boost::gregorian::date next=v[0];
    boost::gregorian::greg_weekday weekDay=next.day_of_week();
    std::cout<<weekDay;
    //printf("next: %s",weekDay.as_long_string());
    

    using namespace boost::gregorian;
    
    greg_year year(1400);
    greg_month month(1);

    // get a month and a year from the user
    try {
      int y, m;
      std::cout << "   Enter Year(ex: 2002): ";
      std::cin >> y;
      year = greg_year(y);
      std::cout << "   Enter Month(1..12): ";
      std::cin >> m;
      month = greg_month(m);
    }
    catch(bad_year by) {
      std::cout << "Invalid Year Entered: " << by.what() << '\n'
        << "Using minimum values for month and year." << std::endl;
    }
    catch(bad_month bm) {
      std::cout << "Invalid Month Entered" << bm.what() << '\n'
        << "Using minimum value for month. " << std::endl;
    }
    
    //date start_of_next_year(year+1, Jan, 1);
    date d(year, month, 1);
    d=(year,month,d.end_of_month());
    date_duration dd(1);
    d += dd;
    
    // print next day
    std::cout << d <<" "<< d.day_of_week() << std::endl;

    return 0;
}

