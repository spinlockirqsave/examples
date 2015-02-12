/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 17, 2014, 3:35 PM
 */

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

/*
 * 
 */
int main(int argc, char** argv) {
    std::ifstream t( "file.txt");
    std::string str;

    t.seekg( 0, std::ios::end);
    str.reserve( t.tellg());
    t.seekg( 0, std::ios::beg);

    str.assign( ( std::istreambuf_iterator<char>( t)),
                    std::istreambuf_iterator<char>());
    return 0;
}

