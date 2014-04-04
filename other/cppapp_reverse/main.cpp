/* 
 * File:   main.cpp
 * Author: piter cf16.eu
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

void reverse( std::string &s)
{
    if ( s.size() == 1)
        return;

    std::string sub = s.substr(1);
    reverse(sub);
    s = sub + s.at(0);
}

int main(int argc, char** argv) {
    std::string s("string");
    std::string s_b;
    
    std::copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, ""));
    
    std::reverse(s.begin(), s.end());
    std::copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, ""));
    
    s = "string";
    std::reverse_copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, ""));
    
    s = "string";
    reverse( s);
    std::copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, ""));
    
    return 0;
}

