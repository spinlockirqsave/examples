/* 
 * File:   main.cpp
 * Author: peter
 *
 * Created on May 28, 2014, 2:19 AM
 */

# include <stdio.h>
# include <ios>
# include <iostream>
# include <iomanip>

#include <cstdlib>

using namespace std;
int main(int argc, char** argv) {
   char buffer[30];
   double x = 5.0;
   sprintf(buffer, "%a", 1.3);
   sscanf(buffer, "%la", &x);
   cout << "    Example 1.2 buffer -> " << buffer << endl;
   cout << "    Example 1.2 scanf <- " << x << endl;

   return 0;
}

