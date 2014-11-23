/* 
 * File:   main.cpp
 * Author: peterg
 *
 * Created on November 22, 2014, 11:09 PM
 */

#include <iostream>
#include <string>

/*
 * All that we have to do is to overwrite char_traits behavior
 * for equality and lass-than comparators
 * and inherit everything other than that from std::char_traits<char>.  
 */
struct ci_char_traits : public std::char_traits<char>
{
    static bool eq( char c1, char c2) {
        return toupper( c1) == toupper( c2);
    }
    
    static bool lt( char c1, char c2) {
        return toupper( c1) < toupper( c2);
    }

    static int compare( const char *c1, const char *c2, size_t n) {
        while( --n > 0 && eq( *c1, *c2)) {
            ++c1;
            ++c2;
        }
        return ( n >= 0? toupper( *c1) - toupper( *c2) : 0);
    }
};
/*
 * 
 */
int main( int argc, char** argv) {

    return 0;
}

