/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on June 22, 2014, 2:10 AM
 */


#include <iostream>

bool find_in_string(int pos, std::string s, std::string str)
{
    std::string str_s = str.substr(pos, s.length());
    int s_pos = 0;

    while (!s.empty()) {
        std::size_t found = str_s.find(s[0]);
        if (found != std::string::npos) {
            s.erase(0, 1);
            str_s.erase(found, 1);
        } else return 0;

    }

    return 1;
}

bool find_in_string(std::string s, std::string str)
{
    bool found = false;
    int pos = 0;

    while (!found && pos < str.length() - s.length() + 1) {
        found = find_in_string(pos++, s, str);
    }

    return found;
}

int main() {

    std::string s1 = "abcdpqrs";
    std::string s2 = "adcbpqrs";
    std::string searched = "dcb";
    std::string searched2 = "pdq";
    std::string searched3 = "bcpq";
    std::cout << find_in_string(searched, s1);
    std::cout << find_in_string(searched, s2);
    std::cout << find_in_string(searched2, s1);
    std::cout << find_in_string(searched3, s1);

    return 0;
}

