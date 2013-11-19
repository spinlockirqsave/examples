/* 
 * File:   main.cpp
 * Author: piotruś piter cf16.eu
 *
 * Created on November 19, 2013, 1:18 AM
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
/*
 * 
 */
int main(int argc, char** argv) {
    std::string s("string");
    std::string s_b;
    
    std::copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, ""));
    
    std::reverse(s.begin(), s.end());
    std::copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, ""));
    
    std::reverse_copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, ""));
    return 0;
}

