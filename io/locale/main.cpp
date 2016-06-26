/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on March 10, 2014, 10:46 PM
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

int main(int argc, char** argv) {
    
    std::locale loc0;                 // copy of the current global locale
    std::locale loc1 = std::locale(); // copy of the current global locale
    std::locale loc2("");            // copy of ‘‘the user’s preferred locale’’
    std::locale loc3( "C");                     // copy of the "C" locale
    std::locale loc4 = std::locale::classic();  // copy of the "C" locale
    std::locale loc5( "POSIX"); // copy of the implementation-defined "POSIX" locale
    
    /* copy of loc5 using numpunct<char> from loc4 */
    std::locale loc6 = loc5.combine< std::numpunct<char> > ( loc4);
    
    printf( "name of current global locale:%s\n", std::locale().name().c_str());
    printf( "name of classic C locale:%s\n", std::locale::classic().name().c_str());
    printf( "name of user's preffered current locale:%s\n", std::locale("").name().c_str());
    printf( "name of current cin locale:%s\n", std::cin.getloc().name().c_str());
    std::cin.imbue( std::locale("en_US.UTF-8"));
    printf( "name of current cin locale:%s\n", std::cin.getloc().name().c_str());
    
    std::locale loc7( "en_US.UTF-8");
    
    std::collate<char>* c = new std::collate_byname<char>( "C");

    return 0;
}