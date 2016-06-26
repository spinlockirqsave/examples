/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on August 27, 2013, 12:15 AM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;
/*
 * 
 */
class A {
public:

    A() {
        printf("A\n");
    }

    virtual ~A() {
        printf("~A\n");
    } //better make it virtual

    static void* operator new(size_t t) {
        printf("A new, with size %ld\n", t);
        ::operator new(t);
    }

    static void operator delete(void* t) {
        printf("A delete\n");
        ::operator delete(t);
    }

    static void* operator new[](size_t t) {
        printf("A new[] with size %ld\n", t);
        ::operator new(t);
    }

    static void operator delete[](void* t) {
        printf("A delete[]\n");
        ::operator delete[](t);
    }

    void check_B() {
        b = new B();
        ::operator delete(b);
    }

    class B {
    public:

        B() {
            printf("B\n");
        }

        ~B() {
            printf("~B\n");
        }
    };

    B* b;
};

class C : public A {
public:
    C(){printf("C\n");}
    ~C(){printf("~C\n");}
    int t[100];
};

int main(void)
{
    A* a = new A;
    A* a2 = new A[10];
    printf("\n------\n");
    a->check_B();
    printf("\n------\n");
    delete a;
    
    C* c = new C;
    A* cc = new C;
    
    delete c;
    delete cc;
    delete [] a2;
return 0;
}

