/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on September 18, 2013, 1:44 AM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

/*
 * 
 */
struct X
{
    template <typename> static bool f() { return true; }
};

struct Y : public X
{
    using X::f;
    template <int> static bool f() { return false; }
};

int main()
{
    std::cout << Y::f <140>() << " " << Y::f <0>() << std::endl;
}

