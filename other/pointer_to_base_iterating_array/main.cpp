/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 26, 2014, 2:39 PM
 */

#include <iostream>

class Foo {
public:
    char a;
    char b;
    char c;
    char d;
    char e[300];
    Foo() : a( 'a') {}
};

class Bar : public Foo{
public:
    int b;
    int t[10];
    int c;
    Bar() : b( 9) { new (this) Bar(7);}
    Bar( int i) : b(65), c(i) {}
};
/*
 * 
 */
int main(int argc, char** argv) {

    Bar *pf = new Bar[100]();
    Foo *pb; // oops
    for( pb = pf; pb != &pf[100]; ++pb) {  
        std::cout << pb->a << std::endl; // somewhere here run will fail
        std::cout << pb->b << std::endl; // somewhere here run will fail
        std::cout << pb->c << std::endl; // somewhere here run will fail
        std::cout << pb->d << std::endl; // somewhere here run will fail
    }
    delete [] pf;
    return 0;
}

