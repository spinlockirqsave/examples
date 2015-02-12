/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on March 25, 2014, 10:52 AM
 */

#include <iostream>
#include <locale>

struct my_numpunct : public std::numpunct<char> {
        typedef char char_type;
        typedef std::string string_type;
        
        explicit my_numpunct( size_t r = 0) : std::numpunct<char>( r) {}

//        char do_decimal_point() const { return ',';}  // comma
        char do_thousands_sep() const { return ' ';}  // space
        string_type do_grouping() const { return "\1\2\3";}   // 3-digit groups
};


/*
 * 
 */
int main(int argc, char** argv) {

    std::cout << "Style A:";
    int i1;
    double d1;
    std::cin >> i1 >> d1; // read using standard "12345678" format
    std::cout << i1 << d1;
    std::cout << 12345678;
    
    std::cin.imbue( std::locale( std::cin.getloc(), new my_numpunct));
    std::cout.imbue( std::locale( std::cout.getloc(), new my_numpunct));
    std::cout << 12345678;
    
    std::cout << "Style B:";
    int i2;
    double d2;
    std::cin >> i2 >> d2; // read using standard "12 345 678" format
    std::cout << i2 << d2;
    std::cout << 12345678;
    
    return 0;
}