/* 
 * File:   main.cpp
 * Author: piotruś peter cf16.eu
 *
 * Created on October 27, 2013, 2:10 PM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */

struct Foo {
void add1(int a, int b) {
    a++;
}

void add2(int &a) {
   a++; 
}
};

void add1(int a, int b) {
    a++;
}

void add2(int &a) {
   a++; 
}

inline static void add3(int a) __attribute__((always_inline));
inline void add3(int a) {
   a++; 
} // does nothing, a won't be changed

inline static void add4(int& a) __attribute__((always_inline));
inline void add4(int &a) {
   a++; 
} // changes the value of a


inline int f() { return 43; }

int main(int argc, char** argv) {

    int a = 31;
    add1(29,28);
    add2(a);
    Foo f;
    int b = 30;
    f.add1(29,28);
    f.add2(b);
    add3(b);
    add4(b);
    return 0;
}

