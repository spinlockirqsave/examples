/* 
 * File:   main.cpp
 * Author: piter cf16.eu
 *
 * Created on October 13, 2013, 1:08 AM
 */

#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

/*
 * 
 */

int gcd_iterative1(int a, int b)
{
    int c;

    if ( b == 0 ) 
        return a;
    else
        while ( b != 0 )
        {
            c = b;
            b = a % b;
            a = c;
        }

        return a;
}

int gcd_iterative(int a, int b, int& x, int& y)
{
    int c;
    std::vector<int> r,q, x_coeff, y_coeff;
    
    x_coeff.push_back(1); y_coeff.push_back(0);
    x_coeff.push_back(0); y_coeff.push_back(1);

    if ( b == 0 ) return a;

    while ( b != 0 )
        {
            c = b;
            q.push_back(a/b);
            r.push_back(b = a % b);
            a = c;
            
            x_coeff.push_back( *(x_coeff.end()-2) -(q.back())*x_coeff.back());
            y_coeff.push_back( *(y_coeff.end()-2) -(q.back())*y_coeff.back());
        }
    if(r.size()==1) {
        x = x_coeff.back();
        y = y_coeff.back();
    } else {
        x = *(x_coeff.end()-2);
        y = *(y_coeff.end()-2);
    }
    std::vector<int>::iterator it;
    std::cout << "r: ";
    for(it = r.begin(); it != r.end(); it++) {
        std::cout << *it << "," ;
    }
    std::cout << "\nq: ";
    for(it = q.begin(); it != q.end(); it++) {
        std::cout << *it << "," ;
    }
    std::cout << "\nx: ";
    for(it = x_coeff.begin(); it != x_coeff.end(); it++) {
        std::cout << *it << "," ;
    }
    std::cout << "\ny: ";
    for(it = y_coeff.begin(); it != y_coeff.end(); it++) {
        std::cout << *it << "," ;
    }
        return a;
}

int main(int argc, char** argv) {

    int i = gcd_iterative1(120,23);
    int j = gcd_iterative1(12,8);
    
    int k = gcd_iterative1(120,23);
    
    //120x+23y=gcd
    int x_solution, y_solution;
    int greatestCommonDevisor =  gcd_iterative(120, 23, x_solution, y_solution);
    greatestCommonDevisor =  gcd_iterative(12, 4, x_solution, y_solution);
    greatestCommonDevisor =  gcd_iterative(8, 3, x_solution, y_solution);
    
    int l = gcd_iterative1(4,6);
    
    return 0;
}

