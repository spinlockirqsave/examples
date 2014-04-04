/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on July 28, 2013, 7:00 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <boost/shared_ptr.hpp>

using namespace std;

int f(int i){return i;}
class A{
public:
    int a;
    int b;

protected:
    int c;
};

class B : protected A{
public:
    A::b;
};
class C : private B{
public:
    B::a;
    B::c;
};

/*
 * 
 */
int main(int argc, char** argv) {

    int i = f(1.0);
    return 0;
}

