/* 
 * File:   main.cpp
 * Author: Piotr Gregor  peter@cf16.eu
 *
 * Created on October 13, 2013, 10:43 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    float x = 0.1;
    float y = 1.1;
    float res = x + y;
    cout<<setprecision(20)<<x << endl;
    cout<<setprecision(20)<<y;
    return 0;
}

