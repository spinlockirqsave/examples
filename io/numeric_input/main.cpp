/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 25, 2014, 10:52 AM
 */

#include <iostream>
#include <locale>

class my_numpunct : public std::numpunct<char> {
    public:
        typedef char char_type;
        typedef std::string string_type;
        
        explicit my_numpunct( size_t r = 0) : std::numpunct<char>( r) {}
    protected:
        char do_decimal_point() const { return '+';}  // comma
        char do_thousands_sep() const { return ' ';}  // space
        string_type do_groupig() const { return "\003";}   // 3-digit groups
};


/*
 * 
 */
int main(int argc, char** argv) {

    std::cout << "Style A:";
    int i1;
    double d1;
    std::cin >> i1 >> d1; // read using standard "12345678" format
    
    std::locale loc( std::locale::classic(), new my_numpunct);
    std::cin.imbue( loc);
    
    std::cout << "Style B:";
    int i2;
    double d2;
    std::cin >> i2 >> d2; // read using standard "12 345 678" format
    
    return 0;
}

