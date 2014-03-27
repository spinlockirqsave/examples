/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 27, 2014, 10:41 AM
 */

#include <iostream>
#include <locale>
#include <string>

int count_spaces( const std::string& s, const std::locale& loc) {
    if( std::has_facet<std::ctype<char> >( loc)) {
        const std::ctype<char>& ct = std::use_facet<std::ctype<char> >( loc);
        int count = 0;
        for( std::string::const_iterator p = s.begin(); p != s.end(); ++p) {
            if( ct.is( std::ctype_base::space, *p))
                ++count;
        }
        return count;
    } else
        return -1;
}
/*
 * 
 */
int main(int argc, char** argv) {

    std::string s = "There are 4 spaces here.";
    int i = count_spaces( s, std::locale());
    return 0;
}

