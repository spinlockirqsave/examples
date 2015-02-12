/* 
 * File:   main.cpp
 * Author: Piotr Gregor  peter@cf16.eu
 *
 * Created on October 6, 2013, 4:20 PM
 */

#include <iostream>
template<typename Tag, typename Tag::type M>
struct Rob { 
  friend typename Tag::type get(Tag) {
    return M;
  }
};

// use
struct A {
  A(int a):a(a) { }
private:
  int a;
};

// tag used to access A::a
struct A_f { 
  typedef int A::*type;
  friend type get(A_f);
};

template struct Rob<A_f, &A::a>;

class B
{
public:
    B(){ val = 0; p = new int;  }
    //void fun_1()const{ val = 1; }  not allowed
    void fun_2()const{ *p = 1; }
    void display()const{ std::cout<< val <<' '<< *p << std::endl; }
private:
    int val;
    const int * p;
};

int main() {
  A a(42);
  std::cout << "proof: " << a.*get(A_f()) << std::endl;
}

