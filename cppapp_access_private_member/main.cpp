/* 
 * File:   main.cpp
 * Author: Piotr Gregor  postmaster@cf16.eu
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

int main() {
  A a(42);
  std::cout << "proof: " << a.*get(A_f()) << std::endl;
}

