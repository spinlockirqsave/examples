/* 
 * File:   main.cpp
 * Author: Piotr Gregor  piter@cf16.eu
 *
 * Created on August 17, 2013, 3:51 PM
 */

#include <cstdlib>
using namespace std;
#include <vector>
#include <stdio.h>
#include <iostream>
#include <limits>

/*
 * 
 */

void f(int i){
    printf("i: %d\n",i);
    vector<int> v(i);
    printf("vector size: %d", v.size());
}

int main(int argc, char** argv) {
    //f(1); // vector size: 1
    try{
    f(-1); // terminate called after throwing an instance of 'std::bad_alloc'
           //what():  std::bad_alloc
    }catch(std::bad_alloc& e){
        printf("tried to allocate");
    }
    
    std::cerr<<"\nstd::vector<int>::size_type(-1)"<<std::vector<int>::size_type(-1);
    std::cerr<<"\n\nstd::vector<int>().max_size()"<<std::vector<int>().max_size();
    std::cerr<<"\nstd::vector<char>().max_size()"<<std::vector<char>().max_size();
    std::cerr<<"\n\nnumeric_limits<unsigned long int>().max(): "<<numeric_limits<unsigned long int>().max();
    std::cerr<<"\nnumeric_limits<int>().max(): "<<numeric_limits<int>().max();
    cout<<"sizeof(int*)"<<sizeof(int*);
    return 0;
}

