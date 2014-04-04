/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 29, 2013, 3:57 AM
 */

#include <iostream>
#include <stdexcept>

using namespace std;

int throw_it() {
    throw range_error( "foo" );
    return 19;
}

int main() {
    try {
        try {
            throw throw_it();
        } catch (...) {
            cerr << "not good!";
        }
    } catch (exception const &e) {
        cerr << e.what() << endl;
        return 0;
    }

    //throw throw_it();
    try {
        throw range_error("range_error again!");
    } catch (range_error& e) {
        cerr << "range_error catched\n";
    }
    
    return 0;
}

