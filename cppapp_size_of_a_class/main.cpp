/* 
 * File:   main.cpp
 * Author: piotruś czyli piter cf16 eu
 *
 * Created on November 27, 2013, 11:27 PM
 */

#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

/*
 * 
 */

class a{
    
};

class aprim{
    int i;
};

class aprimprim{
    virtual void f(){}
};

class aprimx3{
    virtual void f(){}
    int i;
};

int main(int argc, char** argv) {

    cout<<"a: "<<sizeof(a)<<endl;                  // amd x64: 1
    cout<<"aprim: "<<sizeof(aprim)<<endl;          // amd x64: 4
    cout<<"aprimprim: "<<sizeof(aprimprim)<<endl;  // amd x64: 8
    cout<<"aprimx3: "<<sizeof(aprimx3)<<endl;      // amd x64: 16, not 12 because of 8-alignment (8 because the pointer is 8 bytes)
    return 0;
}

