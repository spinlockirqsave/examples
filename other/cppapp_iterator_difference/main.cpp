/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on September 9, 2013, 11:10 PM
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    vector<string> s(10,"s");
    vector<string>::iterator it=s.begin();
    it++; it++; it++; it++;
    vector<string>::difference_type d = it-s.begin();
    
    cout<<d;
    return 0;
}

