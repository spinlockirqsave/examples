/* 
 * File:   main.cpp
 * Author: postmaster cf16.eu
 *
 * Created on August 27, 2013, 12:15 AM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;

/*
 * 
 */
class A
{
public:
    A(){printf("A\n");}
    ~A(){}
    static void* operator new(size_t t){
        printf("A new\n");
        ::operator new(t);
    }
    static void operator delete(void* t){
        printf("A delete\n");
        ::operator delete(t);
    }
    
    void check_B(){
        b = new B();
        ::operator delete(b);
    }

    class B{
    public:
        B(){}
    };
    
    B* b;
};

class C : public A {
public:
};

int main(void)
{
    A* a = new A;
    printf("\n------\n");
    a->check_B();
    printf("\n------\n");
    delete a;
    
    C* c = new C;
    A* cc = new C;
    
    delete c;
    delete cc;
return 0;
}

