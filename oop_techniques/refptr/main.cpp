/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on February 17, 2015, 12:59 PM
 */

#include <cstdlib>
using namespace std;

#include <cstddef>
#include <iostream>
using namespace std;

template<class T>
class Rp {
    public:
	T* p_;
	Rp( T* p) : p_(p) {}
        Rp( Rp const& o)
        {
            p_ = o.p_;
        }
        Rp& operator=( Rp const& o)
        {
            p_ = o.p_;
            return *this;
        }
        ~Rp()
        {
            delete p_;
        }
        operator void*() { return p_;}
};

class A {
	public:
	int i;
};

class B {
	public:
	int i;
};

int main(int argc, char** argv) {
	Rp<A> arp = 0;
        //B* ap = arp.p_;
        if( !arp) cout << "oo!";
	return 0;
}

