/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 9, 2014, 8:05 PM
 * http://stackoverflow.com/questions/22286604/find-digital-roots-of-a-number/22286842#22286842
 * http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=115
 * 
 */

/*
 * 
 */
#include <iostream>
using namespace std;

int main() {
    unsigned long long cc = 0;
    cin >> cc;
        unsigned long int sum = 0;
        while (cc > 0) {
            sum += cc % 10;
            cc = cc / 10;
            if ( sum > 9) { cc = sum; sum = 0; }
        }
    cout << sum;
}