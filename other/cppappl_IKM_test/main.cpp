/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on July 14, 2013, 5:11 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <boost/shared_ptr.hpp>

using namespace std;

class A{
public:
    int a;
    int b;

protected:
    int c;
};

class B : protected A{
public:
    A::b;
};
class C : private B{
public:
    B::a;
    B::c;
};

void foo(long l){
    long l1=l;
}

template<class T>
class Some{
public:
    static int stat;
};

template<class T>
int Some<T>::stat = 10;
/*
 * 
 */
int getSize(){
    return 10;
}


class Person{
public:
    string* namePtr;
    int p;
public:
    Person(){
        namePtr=new string;
    }
    double avg(){return 2.0;}
    void setName(char* s){
        *namePtr=s;
    }
};

int elements[100];
int& getElement(int i){
    return elements[i];
}

int main(int argc, char** argv) {

    getElement(10)=10;
    int o=0;
//    for(char idx=0;idx<250;idx++){
//        int ppp=1;
//        
//        if(idx==248){
//            int u=9;
//        }
//    }
    
    Some<int>::stat = 5;
    printf("%d\t",Some<int>::stat);
    printf("%d\t",Some<char>::stat);
    printf("%d\t",Some<float>::stat);
    printf("%d\t",Some<long>::stat);
    
    int size=getSize();
    char message[size];
    
    boost::shared_ptr<int> i_ptr = boost::shared_ptr<int>();
    i_ptr.reset(new int());
    
    short high=0x0060;
    short low=0x0003;
    short res=low|high;
    
//    Person p;
//    Person c;
//    p.setName("Tom");
//    c=p;
//    printf("%s",c.namePtr);
    for(double d=1.0;d<1.9;d+=0.1){}
    double (Person::*f)()=&Person::avg;
    
    int ii=2;
    switch(ii){
        default:
            break;
            ii=8;
        case 2:
            printf("22222222222");
    }
    
    int Person::*ptr=&Person::p;
    return 0;
}

