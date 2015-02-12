/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 25, 2014, 1:26 AM
 */

#include <iostream>

template< class T, class U>
class PoolFriendly {
protected:
    union  {
        U *rep;                 // for objects in use
        T *next;                // for objects on free list
    };
};

class Something : public PoolFriendly<int, double> {
public:
    Something() {
        rep = new double( 90.0);
    }
};
/*
 * 
 */
int main(int argc, char** argv) {

    Something* ps = new Something;
    delete ps;
    return 0;
}

