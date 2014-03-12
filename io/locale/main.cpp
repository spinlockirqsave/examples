/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 10, 2014, 10:46 PM
 */

#include <string>


#include <locale>
#include <cmath>
#include <stdio.h>
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
    
    printf( "name of current global locale:%s", std::locale().name().c_str());
    printf( "name of classic C locale:%s", std::locale::classic().name().c_str());
    printf( "name of user's preffered current locale:%s", std::locale("").name().c_str());
    
    std::locale loc6( "en_US.UTF-8");
    
    return 0;
}