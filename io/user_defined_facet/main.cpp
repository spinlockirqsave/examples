/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 20, 2014, 03:57 AM
 */

#include <string>
#include <locale>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdint.h>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <limits>
/*
 * 
 */

enum Season { spring, summer, fall, winter};

class Season_io : public std::locale::facet {
    public:
        Season_io( int i = 0) : std::locale::facet( i) {}
        ~Season_io() {} // make possible to destroy Season_io object
        
        /* string representation of x */
        virtual const std::string& to_str( Season x) const = 0;
        
        /* place Season corresponding to s in x */
        virtual bool from_str( const std::string& s, Season& x) const = 0;
        
        /* facet identifier object*/
        static std::locale::id id;
};

std::locale::id Season_io::id;  // definition

int main(int argc, char** argv) {
    
    std::locale loc0;                 // copy of the current global locale
    std::locale loc1 = std::locale(); // copy of the current global locale
    std::locale loc2("");            // copy of ‘‘the user’s preferred locale’’
    std::locale loc3( "C");                     // copy of the "C" locale
    std::locale loc4 = std::locale::classic();  // copy of the "C" locale
    std::locale loc5( "POSIX"); // copy of the implementation-defined "POSIX" locale
    
    char c = std::use_facet< std::numpunct<char> > ( std::locale()).decimal_point();
    std::cout << "std::use_facet< std::numpunct<char> > ( std::locale()).decimal_point():" << c << std::endl;

    return 0;
}