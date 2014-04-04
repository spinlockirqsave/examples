// Boost shared_ptr_example2_test main program  ------------------------------//

//  Copyright Beman Dawes 2001.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org/libs/smart_ptr for documentation.


// Pimpl:
//One common usage of shared_ptr is to implement a handle/body (also called pimpl) 
//idiom which avoids exposing the body (implementation) in the header file.
//The shared_ptr_example2_test.cpp sample program includes a header file, 
//shared_ptr_example2.hpp, which uses a shared_ptr<> to an incomplete type to hide 
//the implementation. The instantiation of member functions which require a complete 
//type occurs in the shared_ptr_example2.cpp implementation file. 
//Note that there is no need for an explicit destructor. Unlike ~scoped_ptr,
//~shared_ptr does not require that T be a complete type.

#include "shared_ptr_example2.hpp"

int main()
{
  example a;
  a.do_something();
  example b(a);
  b.do_something();
  example c;
  c = a;
  c.do_something();
  return 0;
}
