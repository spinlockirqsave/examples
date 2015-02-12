/* 
 * File:   main.cpp
 * Author: peter cf16.eu
 *
 * Created on October 27, 2013, 3:57 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
using namespace std;

/*
 * g++ finline-functions -S main.cpp
 */
int main(int argc, char** argv) {
    /* we solve the linear system
     * ax+by=e
     * cx+dy=f
     */
    if(argc != 7) {
        cerr<<"Cramer equations system: error, we need a,b,c,d,e,f parameters.\n";
        return -1;
    }
    double a,b,e;
    double c,d,f;
    //a=*argv[0];
    sscanf(argv[1],"%lf",&a);
    sscanf(argv[2],"%lf",&b);
    sscanf(argv[3],"%lf",&e);
    sscanf(argv[4],"%lf",&c);
    sscanf(argv[5],"%lf",&d);
    sscanf(argv[6],"%lf",&f);
    
    double determinant = a*d - b*c;
    if(determinant != 0) {
    double x = (e*d - b*f)/determinant;
    double y = (a * f - e * c) / determinant;
        printf("Cramer equations system: result, x = %f, y = %f\n", x, y);
    } else {
        printf("Cramer equations system: determinant is zero\n"
                "there are either no solutions or many solutions exist.\n");
    }
    return 0;
}

