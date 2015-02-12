/* 
 * File:   main.cpp
 * Author: peter cf16.eu
 *
 * Created on November 1, 2013, 4:28 PM
 */

//#include <cstdlib>
#include <iostream>
#include <complex>
using namespace std;
/*
 * 
 */
//int main(int argc, char** argv) {
//    double pi = 3.1415926535897;
//    double N = 512;
//    double M = 512;
//    double lambda = 0.00001;//632e-9;
//    double X = 12.1e-6;
//    double k = (2 * pi) / lambda;
//    double z0 = (N * pow(X, 2)) / lambda;
//    std::complex<double> hx, hy;
//    std::complex<double> j(0,1);
//        hy = (exp(j*k*z0) / (j*lambda))*exp(j*pi/(z0*lambda)*pow(X,2)*pow(j,2));
//        cout << hy <<endl;
//    return 0;
//}
#include <iostream>
#include <complex>

using namespace std;

int main (){
  complex<double> mycomplex(0,1);
  double pi = 3.1415926535897;
  double N = 512;
  double M = 512;
  double lambda = 632e-9;
  double X = 12.1e-6;
  double k = (2*pi)/lambda;
  double z0=(N*pow(X,2))/lambda;
  complex<double> hy;
  for (int j=0; j < N; j++){
      hy = (exp(mycomplex*k*z0) / (mycomplex*lambda))*exp(mycomplex*pi/(z0*lambda)*pow(X,2)*pow((double)j,2));
      cout << hy <<endl;
  }
  //system("pause");
  return 0;
}
