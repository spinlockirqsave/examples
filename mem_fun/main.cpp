/* 
 * File:   main.cpp
 * Author: Piotr Gregor  postmaster@cf16.eu
 *
 * Created on October 21, 2013, 11:54 PM
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <functional>
using namespace std;

//note: adaptors defined in /usr/include/c++/4.4/bits/stl_function.h
// 20.3.8 adaptors pointers members
  /** @defgroup memory_adaptors Adaptors for pointers to members
   * @ingroup functors
   *
   *  There are a total of 8 = 2^3 function objects in this family.
   *   (1) Member functions taking no arguments vs member functions taking
   *        one argument.
   *   (2) Call through pointer vs call through reference.
   *   (3) Const vs non-const member function.
   *
   *  All of this complexity is in the function objects themselves.  You can
   *   ignore it by using the helper function mem_fun and mem_fun_ref,
   *   which create whichever type of adaptor is appropriate.
   *
   *  @{
   */
  /// One of the @link memory_adaptors adaptors for member
  /// pointers@endlink.
/*
template<typename _Ret, typename _Tp>
    class mem_fun_t : public unary_function<_Tp*, _Ret>
    {
    public:
      explicit
      mem_fun_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }

      _Ret
      operator()(_Tp* __p) const
      { return (__p->*_M_f)(); }

    private:
      _Ret (_Tp::*_M_f)();
    };
 * 
 * // Mem_fun adaptor helper functions.  There are only two:
  // mem_fun and mem_fun_ref.
  template<typename _Ret, typename _Tp>
    inline mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)())
    { return mem_fun_t<_Ret, _Tp>(__f); }
 */
class Shape {
public:
    void draw() { std::cout<<"draw"; }
};

void draw_all_shapes(std::list<Shape*>& lsp) {
    for_each(lsp.begin(), lsp.end(), std::mem_fun(&Shape::draw));
    //std::mem_fun(&Shape::draw) is a function that returns object
    //of type mem_fun_t<R,T>. This object is a functor
}

int main(int argc, char** argv) {
    Shape a,b;
    std::list<Shape*> lsp;
    lsp.push_back(&a);
    lsp.push_back(&b);
    draw_all_shapes(lsp);
    
    return 0;
}

