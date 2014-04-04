/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on March 16, 2013, 4:01 AM
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
//using namespace std;



/*
 * 
 */
struct unreferenceable {
  int x;
  unreferenceable* operator&() { return NULL; }
};

void print (unreferenceable* m) {
  if (m) std::cout << m->x << '\n';
  else std::cout << "[null pointer]\n";
}

#include <algorithm>
#include <bitset>
#include <math.h>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

int max_binary_ones_stretch ( int N ) {
  const size_t nbits=std::floor(std::log(N)/std::log(2))+1;
  
  std::bitset<64> input(N);
  std::cout<<"\n---------------\n"<<input.to_string()<<"\n---------------\n";
  long unsigned int globalmax=0;
  if(input.any()){
      long unsigned int pos=0;
      while(input._Find_first()<input.size()){
        pos=input._Find_first();
        int maxbit=0;
            do{
                maxbit++;
                pos++;
            }while(input.test(pos));
            if(maxbit>globalmax)globalmax=maxbit;
            N=(N>>pos);
        input=std::bitset<64>(N);
      }
        return globalmax;
  }

        std::cout<<"\n---------------\n"<<nbits<<"globalmax:"<<globalmax;
  return 0;
}

class A {
public:
    virtual void f() { std::cout << "f IN A" << std::endl;} 
    void g(){std::cout << "g IN A" << std::endl;}
};

class B : public A{
    public:
    virtual void f() { std::cout << "f IN B" << std::endl;}   
    void g(){std::cout << "g IN B" << std::endl;}
};

class C : public B{
    public:
    virtual void f() { B::f(); std::cout << "IN C" << std::endl; }
    virtual void caller(){
        void (A::*cb)() = NULL;
        cb = &A::f;
        (this->*cb)();
    }
};

class D : public C{
    public:
    virtual void f() { C::f(); std::cout << "IN D" << std::endl; }
    void test(){
         caller();
    }
};

struct foo {};

struct Z
{
    typedef foo foo_type;

    //void foo();
};


int main(int argc, char** argv) {

    D d;
    d.test(); // IN B IN C IN D
    
    B b;
    b.f();
    b.A::f();
    A* a_ptr=&b;
    a_ptr->g();
    B* b_ptr=&b;
    b_ptr->g();
    
    void* c_ptr=malloc(sizeof(B));
    memcpy(c_ptr,static_cast<void*>(b_ptr),sizeof(B));

    B* b2ptr=new B;
    c_ptr=malloc(sizeof(B));
    memcpy(c_ptr,static_cast<void*>(b2ptr),sizeof(B));
    
    std::vector<B> bv(10);
    
//    bool keepGoing = true;
//    char key = ' ';
//     while (keepGoing){
//       std::cout << "Enter a key" << std::endl;
//       while(_kbhit()){
//         key = _getch();
//         cout << "You entered: " << key << endl;
//       }
//     }
    
    
//    void(*pfn)(unreferenceable*) = std::addressof(print);
//    //void(*pfn)(unreferenceable*)=print;
//    
//    unreferenceable val {10};
//    unreferenceable* foo = &val;
//    unreferenceable* bar = std::addressof(val);//have to use g++ 4.7 not 4.4
//
//    (*pfn)(foo);   // prints [null pointer]
//    (*pfn)(bar);   // prints 10
    std::string s("es");
   
    int i=max_binary_ones_stretch(1834);
    std::cout<<"globalmax:"<<i;
    i=max_binary_ones_stretch(124274);std::cout<<"globalmax:"<<i;
    i=max_binary_ones_stretch(943);std::cout<<"globalmax:"<<i;
    i=max_binary_ones_stretch(4);std::cout<<"globalmax:"<<i;
    i=max_binary_ones_stretch(7);std::cout<<"globalmax:"<<i;
    i=max_binary_ones_stretch(8);std::cout<<"globalmax:"<<i;
    i=max_binary_ones_stretch(114067);std::cout<<"globalmax:"<<i;
    
    unsigned long long userInput;
    int threeDigits;
    std::stringstream ss,s0;
    std::string nr;
        std::cout << "Enter a long long number: " << std::endl;
        std::cin >> userInput;
        int input=userInput;
        int digits;
        while(input>999){
            input=input/1000;
            digits=userInput-input*1000;
            int mdigits=digits;
            while(mdigits<100){s0<<"0";mdigits*=10;}
            std::string s=ss.str();
            ss.str("");
            ss<<","<<s0.str()<<digits<<s;
            userInput=input;
            s0.str("");
        }
        std::string sf=ss.str();
        ss.str("");
        ss<<input<<sf;
        //int lastDigits=userInput-threeDigits*1000;
        //userInput %= 1000;

        std::cout << "Your Number: " << userInput << ";" << digits <<";"<<ss.str()<<std::endl;
    
//    std::string input_str;
//    std::cin>>input_str;
//    int pos = input_str.find_first_of(',');
//    std::string firstname = input_str.substr(pos+1),
//    lastname = input_str.substr(0, pos);
//
//    std::string output_str = firstname + " " + lastname;
//    std::cout<<std::endl<<output_str<<std::endl;
    
    return 0;
}

