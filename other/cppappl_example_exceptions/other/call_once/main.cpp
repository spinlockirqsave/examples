/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on February 17, 2014, 2:38 PM
 */

#include <cstdlib>

using namespace std;

class Foo {
public:
};

class FooWithOnce : public Foo {
public:

    FooWithOnce& operator=(FooWithOnce const& f) {
        return *this;
    }
    
    Foo& operator=( Foo& f) {
        return f;
    }

    void Once() {
        Foo* f = new Foo();
        *this = *f;
    }
};
/*
 * 
 */
int main(int argc, char** argv) {

    FooWithOnce fwo;
    fwo.Once();
    fwo.Once();
    
    Foo* f2 = new FooWithOnce;
    return 0;
}

