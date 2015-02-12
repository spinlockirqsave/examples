/* 
 * File:   main.cpp
 * Author: peter cf16.eu
 *
 * Created on December 1, 2013, 3:49 PM
 */

#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int *ptr;
ptr=new int;


cout<<ptr<<endl;
cout<<&ptr<<endl;


delete ptr;
 //ptr= NULL;

cout<<ptr<<endl;
cout<<&ptr<<endl;

ptr = (int*) 0xffffffff;            //0xffffffff
cout<<ptr<<endl;
ptr = (int*) 0xffffffffffffffff;    //0xffffffffffffffff
cout<<ptr<<endl;
ptr = (int*) 0xffffffffffffffff1;   //0xfffffffffffffff1  truncated
cout<<ptr<<endl;
ptr = (int*) 0xffffffffffffffff321; //0xfffffffffffff321  truncated
cout<<ptr<<endl;
return 0;
}

