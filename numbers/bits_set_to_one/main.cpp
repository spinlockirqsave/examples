/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on January 21, 2014, 11:55 PM
 */

#include <iostream>
#include <bitset>
using namespace std;

unsigned char mask( int first, int last) {
    //return (1 << last) - (1 << first);
    return (1 << (8-first)+1) - (1 << (8-last));
}
/*
 * 
 */
int main(int argc, char** argv) {
    cout << bitset<8>(mask(3,6)) << endl; //prints:00111100
    cout << bitset<8>(mask(2,6)) << endl; //prints:01111100
    cout << bitset<8>(mask(1,3)) << endl; //prints:11100000
    cout << bitset<8>(mask(1,7)) << endl; //prints:11111110
    return 0;
}

