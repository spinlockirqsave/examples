/* 
 * File:   main.cpp
 * Author: piotruś peter cf16.eu
 *
 * Created on November 12, 2013, 2:47 AM
 */

#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

#include <bitset>
/*
 * 
 */

class A{
public:
    A(){ 
        int* t = new int[100];
        std::cout<<"heap used\n";
        delete t;
    }
};
int main(int argc, char** argv) {
    
    A a1;
    //A* a2 = new A;

    std::string beg("data=\"");
    std::string en("\"");
    std::string s("list c s data=\"vi\" c c s data=\"việt nam\" c c s data=\"việt nam ơi\" list");

    std::string::iterator itBeg = s.begin();
    std::string::iterator itEnd;
    
    while(s.end() != (itBeg = std::search(itBeg, s.end(), beg.begin(), beg.end()))) {
        
        itEnd = std::search(itBeg + beg.size(), s.end(), en.begin(), en.end());
        std::string word;
        std::copy(itBeg + beg.size(), itEnd, word.begin());

        std::cout << "Word:" << word.c_str() << std::endl;
        itBeg = itEnd;
    }
    
    int i;
    std::cin>>i;
    std::cout<<std::bitset<8*sizeof(int)>(i);
    return 0;
}

