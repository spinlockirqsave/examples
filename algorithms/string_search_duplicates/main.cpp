/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 17, 2014, 12:45 PM
 */

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <streambuf>

int findDuplicates( std::string& in, std::map<std::string, int>& m) {
    size_t in_s = in.size();
    if ( in_s == 0) return (-1);

    for ( size_t i = 0; i < in_s; i++) {
        size_t pos_beg = i;
        size_t pos_end = pos_beg + 1;
        while ( pos_end < in_s) {
            std::string searched =  in.substr( pos_beg, pos_end - pos_beg);
            if( m.find( searched) != m.end()) {
                ++pos_end;
                continue;
            }
            bool present = false;
            size_t found;
            while( ( found = in.substr( pos_end).find( searched)) != std::string::npos) {
                present = true;
                m[ searched]++;
                pos_end = pos_end + found + searched.size();
            }
            if( !present) 
                break;
            else
            pos_end = pos_beg + searched.size() + 1;
        }
    }
    int max = 0;
    for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
        if (it ->second > max) {
            max = it->second;
        }
    }
    return max;
}

/*
 * 
 */
int main(int argc, char** argv) {

    std::ifstream ifs( "/home/peter/Downloads/Sheetal05Singular.pdf");
    std::string in( ( std::istreambuf_iterator<char>( ifs)),
                      std::istreambuf_iterator<char>());

    std::map<std::string, int> duplicates;
    int rc = findDuplicates( in, duplicates);
    
    std::map<std::string, int>::iterator it = duplicates.begin();
    while( it != duplicates.end()) {
        std::cout << (*it).first << "," << it->second << std::endl;
        ++it;
    }
    return 0;
}
