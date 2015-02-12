/* 
 * File:   main.cpp
 * Author: peter
 *
 * Created on June 14, 2014, 2:06 PM
 */


/*
 * 
 */
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

int main() {
    
    std::string filename = "file.txt", line;
    std::ifstream ifs( filename.c_str(), std::ios::in);
    
    if ( !ifs) // check if the file exists and can be read
        throw std::runtime_error( "cannot open the file");

    std::stringstream buffer; // buffer to store the lines
    
    while ( getline( ifs, line)) {
        
        int previous_value;
        std::istringstream iss( line.substr( line.find_last_not_of(" ")));
        iss >> previous_value;
        buffer << line << "\t" << ( previous_value + 2) << "\n"; // add integer
    }

    std::ofstream ofs( filename.c_str(), std::ios::out); // ofstream buffer
    ofs << buffer.rdbuf(); // write to the file

    return 0;
}

