/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 * http://stackoverflow.com/questions/14099542/c-convert-date-formats
 *
 * Created on March 25, 2014, 2:35 PM
 */

#include <iostream>
#include <sstream>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost::gregorian;
using namespace std;

int main(int argc, char **argv)
{
    int dateIn = 20111201;

    // Read the date in from ISO format as an int
    ostringstream ss;
    ss << dateIn;
    date d( from_undelimited_string( ss.str() ));

    // Set the output format
    date_facet *fct = new date_facet( "%d%b%Y");    // [1]
    locale loc = locale( locale::classic(), fct);

    // Render the date as a string;
    ss.str( "");
    ss.imbue( loc);
    ss << d;
    string dateOut( ss.str() );
    boost::to_upper( dateOut );

    cout << dateOut << endl;
}

