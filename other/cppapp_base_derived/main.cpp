/* 
 * File:   main.cpp
 * Author: piotruś peter 
 *
 * Created on November 17, 2013, 1:12 PM
 */

#include "Z.h"

#include <cstdlib>
    #include <fstream>
    #include <vector>
    #include <string>
    #include <sstream>
    #include <iterator>
    #include <algorithm>
    #include <iostream>
using namespace std;

void printStringA();

class Base {
public:
    void a() { cout<<" basea"; }
    virtual void va() { cout<<" baseva"; }
};

class Derived : public Base {
public:
    void a() { cout<<" deriveda"; }
    void va() { cout<<" derivedva"; }
};
/*
 * 
 */
#define me
#define my me ->
int main(int argc, char** argv) {
    Derived d;
    d.a();
    d.va();
    Base* b = new Base();
    b my a();
    
    cout << Z::x;
    printStringA();
    return 0;
}

