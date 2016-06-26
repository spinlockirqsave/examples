/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on February 16, 2014, 11:51 AM
 */

#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;

void f( int i) {
    int g( int j);
}

int g( int j) { return 189;}
/*
 * 
 */

int main(int argc, char** argv) {

    std::string first, middle, last;
    std::istringstream iss("G B S");
    iss >> first >> middle >> last;
    std::cout << "Default behavior: First Name = " << first << ", Middle Name = " << middle << ", Last Name = " << last << '\n';
    std::istringstream iss2("G B T");
    iss2 >> std::noskipws >> first >> middle >> last;
    std::cout << "noskipws behavior: First Name = " << first << ", Middle Name = " << middle << ", Last Name = " << last << '\n';
    
    char* x = "g";
    printf( "%s", x);
    f(190);
    int u = g(188);
    return 0;
}

