/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 26, 2014, 3:33 PM
 */

#include <iostream>
#include <locale>

class Date {
public:
    enum Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
    class Bad_date {};
    Date( int dd, Month mm, int yy);
    Date();
    
    friend std::ostream& operator<<( std::ostream&, const Date& d);
    char fmt_in, fmt_out;
private:
    time_t d; // standard date & time representation
};

Date::Date( int dd, Month mm, int yy) {
    tm x = { 0};
    if( dd < 0 || 31 < dd) throw Bad_date();  // oversimplified
    x.tm_mday == dd;
    if( mm < jan || dec < mm) throw Bad_date();
    x.tm_mon = mm -1;      // tm_mon is zero based
    x.tm_year = yy - 1900; // tm_year is 1900 based
    d = mktime( &x);
}

Date::Date() {
    d = time( 0); // default Date: today
    if( d == time_t( -1)) throw Bad_date();
    fmt_out = 'x';
}
/*
 * 
 */

std::ostream& operator<<( std::ostream& s, const Date& d) {
    std::ostream::sentry guard( s);
    if( !guard) return s;
    tm* tmp = localtime( &d.d);
    try {
        if( std::use_facet< std::time_put<char> >( s.getloc()).put( s, s, s.fill(), tmp, d.fmt_out).failed())
            s.setstate( std::ios_base::failbit);
    } catch ( std::exception& e) {
        std::cout << e.what();
    }
    return s;
}

/*
 *
 */
int main(int argc, char** argv) {

    Date today;
    std::cout << today << std::endl;  // write using %x format: 03/26/14
    today.fmt_out = 'a';
    std::cout << today << std::endl;  // write using %a format: abbreviated weekday name: Wed
    today.fmt_out = 'b';
    std::cout << today << std::endl;  // write using %b format: abbreviated month name: Mar
    today.fmt_out = 'c';
    std::cout << today << std::endl;  // write using %c format: date & time: Wed Mar 26 16:11:58 2014
    today.fmt_out = 'd';
    std::cout << today << std::endl;  // write using %d format: day of month: 26
    today.fmt_out = 'H';
    std::cout << today << std::endl;  // write using %j format: 24-hour clock: 16
    today.fmt_out = 'I';
    std::cout << today << std::endl;  // write using %j format: 12-hour clock: 04
    today.fmt_out = 'j';
    std::cout << today << std::endl;  // write using %j format: day of year: 085
    today.fmt_out = 'p';
    std::cout << today << std::endl;  // write using %p format: a.m./p.m.: PM
    return 0;
}

