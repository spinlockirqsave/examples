/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on February 10, 2013, 1:30 AM
 */

#include <cstdlib>
#include <iostream>
#include <boost/algorithm/minmax.hpp>
#include <boost/shared_ptr.hpp>
#include <ql/experimental/fx/all.hpp>
#include <map>
using namespace std;

/*
 * 
 */
typedef struct {
      std::string s;
  }re;
  re r;
  std::map<unsigned int, re> var;
  
int f(int argc, char** argv) {
   re res; 
   res.s="hello";
   var[10]=res;
   r.s="global variable";
   var[1]=r;
    
    cout<<"You are alien. please log in:"<<endl<<"login: login"<<endl
            <<"user: password"<<endl<<endl;
    boost::tuple<int> i;
    boost::shared_ptr<int> i_ptr;
    boost::shared_ptr<double> d;
    
    QuantLib::Brent b;
    QuantLib::BlackCalculator bc();
    
    return 0;
}

