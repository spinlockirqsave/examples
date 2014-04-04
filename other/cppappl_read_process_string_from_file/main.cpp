/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on June 4, 2013, 12:52 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream> 
#include <sstream>
#include <vector>
#include <map>
using namespace std;

/*
 * 
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

int main(int argc, char** argv) {

    std::map<std::string, int> map;
    std::ifstream file("file_with_string.txt", std::ifstream::in);
    std::string temp;
    while (std::getline(file, temp)) {
        std::cout << temp << "\n";
        std::vector<std::string> tokens;
        tokens = split(temp, ' ', tokens);

        for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
            std::vector<std::string>::iterator it1 = it;
            std::map<std::string, int>::iterator mapIt = map.find(*it++);
            int number;
            std::istringstream(*it) >> number;
            if (mapIt != map.end()) {
                (mapIt->second) += (number);
            } else {
                map[*it1] = number;
            }

        }
    }

    for (std::map<std::string, int>::iterator it = map.begin(); it != map.end(); it++) {
        std::cout << it->first << " " << it->second << "\n";
    }
    return 0;
}

