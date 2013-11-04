/* 
 * File:   main.cpp
 * Author: postmaster cf16.eu
 *
 * Created on September 10, 2013, 9:00 PM
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class X{
public:
      X(int, int, string){}

private: int a;
         int b;
         string c;
};

class Y{
public:
    Y(int i) : x(i,X(1,2,"some x")) {
        x.push_back(X(2,3,"one more"));
        x.push_back(X(3,4,"and again"));
    }
    int size() { return x.size(); }
private: 
    vector<X> x;
};
/*
 * 
 */
int main(int argc, char** argv) {

    Y y10(10);
    cout<<y10.size();
    
    Y y20(20);
    cout<<y20.size();
    
    return 0;
}

