/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on February 17, 2014, 3:22 PM
 */

#include <iostream>
#include <cassert>

size_t string_count_digits( std::string& s) {
    size_t res = 0;
    for ( size_t i = 0; i < s.length(); ++i) {
        if ( isdigit( s[i])) ++res;
    }
    return res;
}

/*
 * 
 */
int main(int argc, char** argv) {

    std::string s0( "jdjasjhojhjkh"); // 1
    std::string s1( "jdjasjh1jhjkh"); // 1
    std::string s2( "1jhghjgj2jhg");  // 2
    std::string s3( "1jhghjgj2jhg3"); // 3
    
    assert( string_count_digits( s0) == 0);
    assert( string_count_digits( s1) == 1);
    assert( string_count_digits( s2) == 2);
    assert( string_count_digits( s3) == 3);
    return 0;
}

