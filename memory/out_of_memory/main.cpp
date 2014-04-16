/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 16, 2014, 4:34 PM
 */

#include <iostream>
#include <string>

typedef void ( *new_handler)();

template<class T>                    // "mixin-style" base class
class NewHandlerSupport {            // for class specific 
public:                              // set_new_handler support
    static new_handler set_new_handler(new_handler p);
    static void * operator new(size_t size);

private:
    static new_handler currentHandler;
};

template<class T> 
new_handler NewHandlerSupport<T>::currentHandler;      // sets currentHandler
                                    // to 0 (i.e., null) by
                                    // default
template<class T> 
new_handler NewHandlerSupport<T>::set_new_handler( new_handler p)
{
  new_handler oldHandler = currentHandler;
  currentHandler = p;
  return oldHandler;
}

template<class T> 
void* NewHandlerSupport<T>::operator new(size_t size) {
    new_handler globalHandler = // install X's
            std::set_new_handler(currentHandler);       // handler

    void *memory;

    try {                                               // attempt
        memory = ::operator new(size);                  // allocation
    } catch (std::bad_alloc&) {                         // restore
        std::set_new_handler(globalHandler);            // handler;
        throw;                                          // propagate exception
    }

    std::set_new_handler(globalHandler);                // restore handler
    return memory;
}

// note inheritance from mixin base class template. (See
// my article on counting objects for information on why
// private inheritance might be preferable here.)

class X : public NewHandlerSupport<X> {
   // as before, but no declarations for
}; // set_new_handler or operator new

class Y : public NewHandlerSupport<X> {
   // as before, but no declarations for
}; // set_new_handler or operator new


    
void noMoreMemoryForX(){}                          // decl. of function to
                                                   // call if memory allocation
                                                   // for X objects fails
void noMoreMemoryForY(){}
    
/*
 * 
 */
int main(int argc, char** argv) {

    X::set_new_handler(noMoreMemoryForX);
                                                   // set noMoreMemoryForX as X's
                                                   // new-handling function

    X *px1 = new X;                                // if memory allocation
                                                   // fails, call noMoreMemory

    std::string *ps = new std::string;             // if memory allocation
                                                   // fails, call the global
                                                   // new-handling function
                                                   // (if there is one)

    X::set_new_handler(0);                         // set the X-specific
                                                   // new-handling function
                                                   // to nothing (i.e., null)

    X *px2 = new X;                                // if memory allocation
                                                   // fails, throw an exception
                                                   // immediately. (There is
                                                   // no new-handling function
                                                   // for class X.)
    
    Y::set_new_handler(noMoreMemoryForX);
    Y::set_new_handler(noMoreMemoryForY);
                                                   // set noMoreMemoryForY as Y's
                                                   // new-handling function

    Y *py1 = new Y;                                // if memory allocation
                                                   // fails, call noMoreMemory


    return 0;
}

