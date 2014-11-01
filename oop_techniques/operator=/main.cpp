/* 
 * File:   main.cpp
 * Author: peterg
 *
 * Created on November 1, 2014, 12:04 PM
 */

#include <iostream>

class Animal {
public:
    int a;
    Animal& operator= ( const Animal& o) { a = 100; std::cout << "Animal::operator=\n"; return *this; }
};

class Lizard : public Animal {
public:
    int l;
    Lizard& operator= ( const Lizard& o) {
        a = 200;
        l = 200;
        std::cout << "Lizard::operator=\n";
        return *this;
    }
};

class Chicken : public Animal {
public:
    int c;
    Chicken& operator= ( const Chicken& o) {
        Animal::operator=( o);
        a = 300;
        c = 300;
        std::cout << "Chicken::operator=\n";
        return *this;
    }
};

/*
 * 
 */
int main(int argc, char** argv) {

    Lizard l;
    Chicken c;

    Animal *apl = &l;
    Animal *apc = &c;

    *apl = *apc; // only Animal::operator=,                     virtual call
    l = l;       // Lizard::operator=,                          static call       
    
    *apc = *apl; // only Animal::operator=                      virtual call
    c = c;       // Animal::operator= + Chicken::operator=      static call

    return 0;
}

