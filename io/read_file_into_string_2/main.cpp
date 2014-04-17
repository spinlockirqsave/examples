/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 17, 2014, 3:37 PM
 */

#include <string>
#include <fstream>
#include <streambuf>

/*
 * 
 */
int main(int argc, char** argv) {
    std::ifstream t( "file.txt");
    std::string str( ( std::istreambuf_iterator<char>( t)),
                         std::istreambuf_iterator<char>());
    return 0;
}

