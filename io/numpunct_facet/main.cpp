/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on March 23, 2014, 11:49 PM
 */

#include <iostream>
#include <locale>
#include <algorithm>
#include <sstream>

/*
 * 
 */

class my_numpunct : public std::numpunct<char> {
    public:
        typedef char char_type;
        typedef std::string string_type;
        
        explicit my_numpunct( size_t r = 0) : std::numpunct<char>( r) {}
    protected:
        char do_decimal_point() const { return '+';}  // comma
        char do_thousands_sep() const { return ' ';}  // space
        string_type do_grouping() const { return "\003";}   // 3-digit groups
};

void f() {
    std::cout << "current locale:" << std::locale().name();
    std::cout << "style A:" << 1234 << " *** " << 1234.8 << "\n";
    std::locale loc( std::locale(), new my_numpunct);
    std::cout.imbue( loc);
    std::cout << "style B:" << 1234 << " *** " << 1234.8 << '\n';
}

int main(int argc, char** argv) {

    f();
    std::cin.imbue( std::locale( "POSIX"));
    std::cout.imbue( std::locale( "POSIX"));
    return 0;
}