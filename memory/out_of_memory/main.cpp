/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 16, 2014, 4:34 PM
 */

#include <iostream>
#include <string>
#include <cstdio>

typedef void ( *new_handler)();

/* a mixin-style" base class, base class that's designed
 * to allow derived classes to inherit a single specific
 * capability — in this case, the ability to set a class
 * specific new-handler */
template<class T>
class NewHandlerSupport {
public:
    static new_handler set_new_handler(new_handler p);
    static void* operator new(size_t size);
    static void* operator new[](size_t size);

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
    new_handler globalHandler =                         // install X's
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

template<class T> 
void* NewHandlerSupport<T>::operator new[](size_t size) {
    new_handler globalHandler =                         // install X's
            std::set_new_handler(currentHandler);       // handler

    void *memory;

    try {                                               // attempt
        memory = ::operator new[](size);                  // allocation
    } catch (std::bad_alloc&) {                         // restore
        std::set_new_handler(globalHandler);            // handler;
        throw;                                          // propagate exception
    }

    std::set_new_handler(globalHandler);                // restore handler
    return memory;
}

// note inheritance from mixin base class template.
// private inheritance might be preferable here.)

class X : public NewHandlerSupport<X> {
   // as before, but no declarations for
}; // set_new_handler or operator new

class Y : public NewHandlerSupport<Y> {
   // as before, but no declarations for
}; // set_new_handler or operator new


    
void noMoreMemoryForX() {
    std::printf( "noMoreMemoryForX");
    throw std::bad_alloc();
}

void noMoreMemoryForY() {
    std::printf( "noMoreMemoryForY");
    throw std::bad_alloc();
}
    
/*
 * 
 */
int main(int argc, char** argv) {

    X::set_new_handler( noMoreMemoryForX);
                                                   // set noMoreMemoryForX as X's
                                                   // new-handling function
    size_t s = 0x400000000; // 16GB
    try {
    X *px1 = (X*) X::operator new(s);              // if memory allocation
                                                   // fails, call noMoreMemory
    } catch (std::bad_alloc&) { 
        printf( "bad_alloc catched");
    }
    
    try {
    X *px1 = new X[s];                             // if memory allocation
                                                   // fails, call noMoreMemory
    } catch (std::bad_alloc&) { 
        printf( "bad_alloc catched");
    }

//    std::string *ps = new std::string;             // if memory allocation
//                                                   // fails, call the global
//                                                   // new-handling function
//                                                   // (if there is one)
//
//    X::set_new_handler(0);                         // set the X-specific
//                                                   // new-handling function
//                                                   // to nothing (i.e., null)
//
//    X *px2 = new X[s];                                // if memory allocation
//                                                   // fails, throw an exception
//                                                   // immediately. (There is
//                                                   // no new-handling function
//                                                   // for class X.)
//    
    Y::set_new_handler( noMoreMemoryForX);
    Y::set_new_handler( noMoreMemoryForY);

    try {
        Y *py1 = new Y[s];                             // if memory allocation
                                                   // fails, call noMoreMemory
    } catch (std::bad_alloc&) { 
        printf( "bad_alloc catched");
    }


    return 0;
}

