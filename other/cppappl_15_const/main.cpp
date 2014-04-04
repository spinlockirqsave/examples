/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 6, 2013, 2:05 AM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;
/*
 * 
 */
class A{
public:
    A(){}
    int i;
    static void fA(){printf("A\n");}
};
class B : public A{
public:
    void fB(){printf("B\n");}
};
int main(int argc, char** argv) {
    
    const char c = 'c';
    //c='k'; //error: assignment of read-only variable ‘c’
    char* pc;
    //pc=&c; //error: invalid conversion from ‘const char*’ to ‘char*’ [-fpermissive]
    //But:
    char d = 'd';
    const char* dp=&d; //OK
    
//    const char** pcc = &pc; // not allowed
//    *pcc = &c;
//    *pc = 'C'; // would allow to modify a const object
    
        //char c5=(char)49;
        printf("49 as int: %d\n",(char)49);//49
        printf("49 as char: %c\n",(char)49);//1 (48+1)
        
        printf("7 as int: %d\n",(char)7);//7 is BELL in ASCII
        printf("7 as char: %c\n",(char)7);//
        
        for(int i=3;i<50;i++){
            char cx=(char)i;
                printf("%d as int: %d\n",i,cx);//7 is BELL in ASCII
                printf("%d as char: %c\n",i,cx);//
        }
        
        char *s1 =0;
        char sc=(char)0;//printf("0 as int: %d\n",sc); 0  BUT! printf("0 as char: %c\n",sc); =NOTHING, EMPTY
        char sc1='0';//printf("0 as int: %d\n",sc1); 48
        //int si=sc;
        printf("0 as int: %d\n",sc);
        printf("0 as char: %c\n",sc);
        //const char *s2 = s1; // OK...
        //*s1='5';
        //*s1='7';
        char cz=(int)((char)0);
        int zero=(int)(cz);
        printf("int 0 from char: %d\n",zero);
        //char *a[100]; // aka char **
        //const char * const*ps = a; // no error!
        
        int i=99;
        int *i1 =&i ;
        const int *i2 = i1; // OK...
        *i1=5;
        printf("i1: %d, i2: %d\n",*i1,*i2);
        *i1=7;
        printf("i1:%d, i2: %d\n",*i1,*i2);
        
        A a;
        B b;
        b.fB();
        b.fA();
        
        a.i=8;
        const A a1; //need to provide default constructor if A 
        //a1.i=9;//error: assignment of member ‘A::i’ in read-only object
        const A* ac=new A();
        //ac->i=8; //error: assignment of member ‘A::i’ in read-only object
    return 0;
}

