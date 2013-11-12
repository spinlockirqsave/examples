/* 
 * File:   main.cpp
 * Author: piotruś piter cf16.eu
 *
 * Created on November 12, 2013, 2:47 AM
 */

#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
/*
 * 
 */
int main(int argc, char** argv) {

    std::string beg("data=\"");
    std::string en("\"");
    std::string s("list c s data=\"vi\" c c s data=\"việt nam\" c c s data=\"việt nam ơi\" list");

    std::string::iterator itBeg = s.begin();
    std::string::iterator itEnd;
    
    while(s.end() != (itBeg = std::search(itBeg, s.end(), beg.begin(), beg.end()))) {
        
        itEnd = std::search(itBeg + beg.size(), s.end(), en.begin(), en.end());
        std::string word;
        std::copy(itBeg + beg.size(), itEnd, word.begin());

        std::cout << "Word:" << word.c_str() << std::endl;
        itBeg = itEnd;
    }
    return 0;
}

