/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 3, 2014, 12:48 PM
 */

#include <cstdio>
#include <boost/math/distributions/uniform.hpp>

template< class T>
class Handle {
    T* rep_;
    int* pcount_;
    public:
        T* operator->() { return rep_;}
        Handle( T* rep) : rep_( rep), pcount_( new int(1)) {}
        Handle( const Handle& r) : rep_( r.rep_), pcount_( r.pcount_) {
            (*pcount_)++;
        }
        Handle& operator=( const Handle* r) {
            if ( rep_ == r->rep_) return *this;
            if ( --(*pcount_) == 0) {
                delete rep_;
                delete pcount_;
            }
            rep_ = r.rep_;
            pcount_ = r.pcount_;
            (*pcount_)++;
            return *this;
        }
        ~Handle() {
            if ( --(*pcount_) == 0) {
                delete rep_;
                delete pcount_;
                printf( "~Handle()");
            }
        }
};

void f1( Handle<boost::math::uniform_distribution<int> > b) {
    Handle<boost::math::uniform_distribution<int> > a = b;
}

Handle<boost::math::uniform_distribution<int> > f2() {
    Handle<boost::math::uniform_distribution<int> > h( new boost::math::uniform_distribution<int>);
    return h;
}

/*
 * 
 */
int main(int argc, char** argv) {

    Handle<boost::math::uniform_distribution<int> > h = f2();
    f1( h);
    Handle<boost::math::uniform_distribution<int> > k = h;
    return 0;
}

