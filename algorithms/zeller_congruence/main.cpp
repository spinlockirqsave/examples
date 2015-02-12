/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on March 2, 2014, 8:47 PM
 * http://stackoverflow.com/questions/22132390/zellers-congruence-coding-outputing-wrong-day
 * http://en.wikipedia.org/wiki/Zeller's_congruence
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int dayNumber(int m, int d, int y) {
    if ( m == 1 || m == 2) {
        m = m + 12;
        y = y - 1;
    }
    return (d + (int)floor((13 * (m + 1)) / 5) + y%100 + (int)floor((y%100)/ 4) + (int)floor(((int)floor(y/100))/4) + 5*(int)floor(y/100)) % 7;
}

int main() {

    int m, d, y, daynum;
    char ans;

    do {
        cout << "Enter a date as mm dd yyyy: \n";
        cin >> m >> d >> y;
        daynum = dayNumber(m, d, y);
        cout << "daynum:" << daynum << "\t";

        switch (daynum) {
            case 2:
                cout << m << "/" << d << "/" << y << " is a Monday \n";
                break;
            case 3:
                cout << m << "/" << d << "/" << y << " is a Tuesday \n";
                break;
            case 4:
                cout << m << "/" << d << "/" << y << " is a Wednesday \n";
                break;
            case 5:
                cout << m << "/" << d << "/" << y << " is a Thursday \n";
                break;
            case 6:
                cout << m << "/" << d << "/" << y << " is a Friday \n";
                break;
            case 0:
                cout << m << "/" << d << "/" << y << " is a Saturday \n";
                break;
            case 1:
                cout << m << "/" << d << "/" << y << " is a Sunday \n";
                break;
        }
        cout << "Do you want to continue? (y/n) \n";
        cin >> ans;
    } while ((ans == 'y') || (ans == 'Y'));

    return 0;
}

