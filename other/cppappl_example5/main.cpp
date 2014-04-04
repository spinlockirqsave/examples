/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on April 6, 2013, 1:49 PM
 */

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <memory>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    using namespace std;
    string sentence = "Something in the way she moves...";
    istringstream iss(sentence);
    ostringstream oss;
    vector<string> tokens;
    
//    copy(istream_iterator<string>(iss),
//             istream_iterator<string>(),
//             ostream_iterator<string>(cout, "\n"));
    
    copy(istream_iterator<char>(iss),
         istream_iterator<char>(),
         ostream_iterator<char> (oss,"_"));
    
    cout<<oss.str();
    
    return 0;
}

