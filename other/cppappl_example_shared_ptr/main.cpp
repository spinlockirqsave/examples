/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 27, 2013, 7:37 PM
 */

#include <cstdlib>

#include <memory> 
#include <iostream> 
#include <boost/shared_ptr.hpp>
 
void fun(boost::shared_ptr<int> sp)
{
    std::cout << "fun: sp.use_count() == " << sp.use_count() << std::endl; 
}
 
int main() 
{ 
    boost::shared_ptr<int> sp1(new int(5));
    std::cout << "sp1.use_count() == " << sp1.use_count() << std::endl; 
    fun(sp1);
    std::cout << "sp1.use_count() == " << sp1.use_count() << std::endl; 
}

