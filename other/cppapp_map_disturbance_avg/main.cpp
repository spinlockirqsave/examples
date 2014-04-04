/* 
 * File:   main.cpp
 * Author: Piotr Gregor  piter@cf16.eu
 *
 * Created on October 21, 2013, 10:58 PM
 */

#include <cstdlib>
#include <map>
#include <iostream>
#include <math.h>
using namespace std;

/*
 * 
 */

double closest_to_avg(double* arr, size_t size, double avg) {
  std::map<double,double> disturbances;
  for(int p = 0; p < size; p++) {
      double dist = fabs(avg-arr[p]);
        disturbances[fabs(avg-arr[p])]=arr[p]; //if two elements are equally distant
                                              //from avg we take new one
  }
  return disturbances.begin()->second;
}

int main(int argc, char** argv) {
    double arr[] = {1,2,3,4,5,7};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    double c = closest_to_avg(arr,size,3.66667);
    cout<<"c: "<<c<<endl;
    return 0;
}

