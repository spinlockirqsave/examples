/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 20, 2014, 03:57 AM
 */

#include <iostream>
#include <locale>
#include <algorithm>
#include <sstream>

/*
 * 
 */
void f( const std::string& s1, const std::string& s2, const char* n) {
    bool b = s1 == s2;  // compare using implementation's character set values
    
    /* compare() operates on char[]s */
    const char* cs1 = s1.data();
    const char* cs2 = s2.data();
    
    typedef std::collate<char> Col;
    
    const Col& glob = std::use_facet<Col>( std::locale()); // from current global locale
    int i0 = glob.compare( cs1, cs1 + s1.size(), cs2, cs2 + s2.size());
    
    const Col& my_coll = std::use_facet<Col>( std::locale( "")); // from my preferred locale
    int i1 = my_coll.compare( cs1, cs1 + s1.size(), cs2, cs2 + s2.size());
    
    const Col& coll_n = std::use_facet<Col>( std::locale( n)); // from locale named "n"
    int i2 = coll_n.compare( cs1, cs1 + s1.size(), cs2, cs2 + s2.size());
    
    int i3 = std::locale()( s1, s2);  // compare using the current global locale
    int i4 = std::locale( "")( s1, s2);  // compare using the current preferred locale
    int i5 = std::locale( n)( s1, s2);  // compare using the current global locale
}

int main(int argc, char** argv) {

    std::string s1 = "piter1";
    std::string  s2 = "piter2";
    f( s1, s2, "POSIX");
    return 0;
}