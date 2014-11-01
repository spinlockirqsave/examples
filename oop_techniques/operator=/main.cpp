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

/*--------------improvement-----------------------------*/
class Animal2 {
public:
    virtual Animal2& operator= ( const Animal2& o) { std::cout << "Animal2::operator=\n"; return *this; }
};

class Lizard2 : public Animal2 {
public:
    virtual Lizard2& operator= ( const Animal2& o) { std::cout << "Lizard2Animal2::operator=\n"; return *this; }
    Lizard2& operator= ( const Lizard2& o) {
        std::cout << "Lizard2::operator=\n";
        return *this;
    }
};

class Chicken2 : public Animal2 {
public:
    virtual Chicken2& operator= ( const Animal2& o) { std::cout << "Chicken2Animal2::operator=\n"; return *this; }
    Chicken2& operator= ( const Chicken2& o) {
        Animal2::operator=( o);
        std::cout << "Chicken2::operator=\n";
        return *this;
    }
};

/*--------------improvement2-----------------------------*/
class Animal3 {
public:                 // this should be private or protected to make
                        // cross platform Chicken-to-Liazrd assignment disabled
                        // but then also *apl3 = *apl3 wouldn't compile
    virtual Animal3& operator= ( const Animal3& o) { std::cout << "Animal3::operator=\n"; return *this; }
};

class Lizard3 : public Animal3 {
public:
    virtual Lizard3& operator= ( const Animal3& o) { std::cout << "Lizard3Animal3::operator=\n"; return *this; }
    Lizard3& operator= ( const Lizard3& o) {
        std::cout << "Lizard3::operator=\n";
        return *this;
    }
};

class Chicken3 : public Animal3 {
public:
    virtual Chicken3& operator= ( const Animal3& o) { std::cout << "Chicken3Animal3::operator=\n"; return *this; }
    Chicken3& operator= ( const Chicken3& o) {
        Animal3::operator=( o);
        std::cout << "Chicken3::operator=\n";
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
                 // and we just assignerd a chicken to lizard !!!!!!!!!!!!!
    l = l;       // Lizard::operator=,                          static call       
    
    *apc = *apl; // only Animal::operator=                      virtual call
    c = c;       // Animal::operator= + Chicken::operator=      static call

    /*--------------improvement-----------------------------*/
    Lizard2 l2;
    Chicken2 c2;

    Animal2 *apl2 = &l2;
    Animal2 *apc2 = &c2;

    *apl2 = *apc2; // virtual Lizard2& operator= ( const Animal2& o),                   virtual call
                 // and we just assignerd a chicken to lizard !!!!!!!!!!!!!
    l2 = l2;       // Lizard2& operator= ( const Lizard2& o)                            static call       
    
    *apc2 = *apl2; // virtual Chicken2& operator= ( const Animal2& o)                   virtual call
    c2 = c2;       // Chicken2& operator= ( const Chicken2& o)                          static call

    /*--------------improvement2-----------------------------*/
    Lizard3 l3;
    Chicken3 c3;

    Animal3 *apl3 = &l3;
    Animal3 *apc3 = &c3;

    *apl3 = *apc3; // it compiles, virtual Lizard3& operator= ( const Animal3& o)       virtual call
    
    *apl3 = *apl3; // it compiles, virtual Lizard3& operator= ( const Animal3& o)       virtual call
    l3 = l3;       // Lizard3& operator= ( const Lizard3& o)                            static call  
    
    *apc3 = *apl3; // virtual Chicken3& operator= ( const Animal3& o)                   virtual call

    c3 = c3;       // Chicken3& operator= ( const Chicken3& o)                          static call

    return 0;
}

