/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on February 16, 2014, 11:51 AM
 */

#include <iostream>
#include <sstream>
using namespace std;

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
    return 0;
}

