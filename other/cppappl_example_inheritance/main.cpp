/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 30, 2013, 12:52 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <vector>
using namespace std;

/*
 * 
 */
//Class A
class A
{
public:
    int getX(){return _x;};
protected:
    int getX2(){return _x;}
private:
    int _x;
};

//Class B
class B : protected A  //A::getX and A::getX2 are not visible in B interface,
          //^^^^^^^^^    // but still we can use it inside B class: inherited
                       // members are always there, the inheritance mode
                       // affects only how they are accessible outside the class
                       // in particular for a children
{
public:
    int method(){ return this->getX();}
    int method2(){ return this->getX2();}
};

class C{
public:
    class A a;
};

int main(int argc, char** argv) {

    B b=B();
    printf("b.getX(): %d",b.method());  // OK
    printf("b.getX(): %d",b.method2()); // OK
    
    vector<int*> v;
    v.push_back(new int(34));
    printf("v: %d",*v[0]);
    
    C c;
    c.a=A();
    
    return 0;
}

