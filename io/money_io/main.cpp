/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 25, 2014, 5:01 PM
 */

#include <iostream>
#include <locale>

/*
 * 
 */
int main(int argc, char** argv) {

    double d = 12345678;
    std::ostream& s = std::cout;
    std::ostream::sentry guard( s);
    
    try {
        const std::money_put<char>& f = std::use_facet< std::money_put<char> >( s.getloc());
        std::cout << std::use_facet< std::moneypunct<char> >( s.getloc()).curr_symbol();
        std::cout << std::use_facet< std::moneypunct<char> >( s.getloc()).decimal_point();
        std::cout << std::use_facet< std::moneypunct<char> >( s.getloc()).negative_sign();
        if ( f.put( s, true, s, s.fill(), d).failed()) { 
            s.setstate( std::ios_base::badbit);
        }
    } catch ( std::exception& e) {
        std::cout << e.what();
    }
    return 0;
}

