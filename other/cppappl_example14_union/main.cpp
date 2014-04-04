/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 3, 2013, 4:53 PM
 */

#include <cstdlib>

//using namespace std;
typedef int UINT32;
typedef int VECT2;
typedef int INT32;

struct GRID2
{
    INT32 x, y;
};

struct VNODE2
{
    VNODE2 * next;
    VNODE2 * prev;
    UINT32   Flags;
    union
    {
        VECT2 p;
        GRID2 g;
    }myNamedUnion;
}; 

/*
 * 
 */
//int main(int argc, char** argv) {
//
//    VNODE2 v;
//    v.myNamedUnion.g.x=1;
//    return 0;
//}
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class AString{
    public:
        AString() { buf = 0; length = 0; }
        AString( const char*);
        void display() const {std::cout << buf << endl;}
        ~AString() {delete buf;}
        // <-- another member function to be defined
AString & operator=(const AString &other)
{
    if (&other == this) return *this;
    length = other.length;
    delete buf;
    buf = new char[length+1];
    strcpy(buf, other.buf);
    return *this; 
}
    private:
        int length;
        char* buf;
};
AString::AString( const char *s )
{
    length = strlen(s);
    buf = new char[length + 1];
    strcpy(buf,s);
}

int main(void)
{
    AString first, second;
    second = first = "Hello world";
    first.display();
    second.display();
    int i=0;
    for (int i = 0; i < 4; ++ i);
std::cout << i << std::endl;

    int a=7;
    int* mrPointer=&a;
    *mrPointer;
    7;
    a;
    int** iptr; // iptr is on stack
    *iptr=mrPointer;
    int** iptr_h = new int*();// iptr_h is on heap
    *iptr_h=mrPointer;
    
    return 0;
}

