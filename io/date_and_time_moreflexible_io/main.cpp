/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on March 27, 2014, 12:30 AM
 */

#include <iostream>
#include <locale>
#include <string.h>

class Date {
public:
    enum Month { jan = 0, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
    class Bad_date {};
    Date( int dd, Month mm, int yy);
    Date();
    Date( Date& other) : fmt_in( other.fmt_in), fmt_out( other.fmt_out) {
        d = other.d;
    }
    Date& operator=( Date const& other) {
        fmt_in = other.fmt_in;
        fmt_out = other.fmt_out;
        d = other.d;
        return *this;
    }
    
    friend std::ostream& operator<<( std::ostream&, const Date& d);
    char fmt_in, fmt_out;
private:
    time_t d; // standard date & time representation
    static const char fmt[];
};

const char Date::fmt[] = "%A, %B %d, %Y"; // e.g., Wednesday, March 26, 2014

Date::Date( int dd, Month mm, int yy) {
    tm x = { 0};
    if( dd < 0 || 31 < dd) throw Bad_date();  // oversimplified
    x.tm_mday = dd;
    if( mm < jan || dec < mm) throw Bad_date();
    x.tm_mon = mm;         // tm_mon is zero based
    x.tm_year = yy - 1900; // tm_year is 1900 based
    d = mktime( &x);
    fmt_in = 'x';
    fmt_out = 'x';
}

Date::Date() {
    d = time( 0); // default Date: today
    if( d == time_t( -1)) throw Bad_date();
    fmt_in = 'x';
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
        /* put tmp into s using Date::fmt format */
        if( std::use_facet< std::time_put<char> >( s.getloc()).put( 
                s, s, s.fill(), tmp,
                Date::fmt, Date::fmt + strlen( Date::fmt)).failed())
            s.setstate( std::ios_base::failbit);
    } catch ( std::exception& e) {
        std::cout << e.what();
    }
    return s;
}

std::istream& operator>>( std::istream& s, Date& d) {
    std::istream::sentry guard( s);
    if( !guard) return s;
    
    std::ios_base::iostate res = std::ios_base::goodbit;
    tm x = { 0};
    std::istreambuf_iterator<char, std::char_traits<char> > end;
    try {
        std::use_facet< std::time_get<char> >( s.getloc()).get_date( s, end, s, res, &x);
        if( res == 0 || res == std::ios_base::eofbit)
            //d = Date( x.tm_mday, Date::Month( x.tm_mon + 1), x.tm_year + 1900);
            d.operator=( Date( x.tm_mday, Date::Month( x.tm_mon), x.tm_year + 2000));
        else {
            s.setstate( res);
            //s.ignore()
        }
    } catch( std::exception& e) {
        std::cout << e.what();
    }
    return s;
}
/*
 *
 */
int main(int argc, char** argv) {

    try {
        Date today;
        std::cout << today << std::endl; // write using Date::fmt format

        Date dd;
        std::cin >> dd;  // read dates produced by %x format
        std::cout << dd << std::endl; // write using Date::fmt format

        while ( std::cin >> dd && !std::cin.fail()) { // read dates produced by %x format
            dd.fmt_out = 'c';
            std::cout << dd << std::endl; // write using Date::fmt format
        }
    } catch ( Date::Bad_date& bd) {
        std::cout << "exit: bad date caught\n";
    }

    return 0;
}



