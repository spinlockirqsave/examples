/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 10, 2014, 10:46 PM
 */

#include <string>


#include <locale>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdint.h>
#include <bitset>
#include <iostream>
/*
 * 
 */
//typedef char SQLCHAR;
//int main(int argc, char** argv) {
//    uint32_t sum = 0x6f031f1f;
//    uint16_t x = 0x1234;
//    uint16_t* w = &x;
//    uint16_t answer = 0;
//    std::cout << std::bitset<16>(*w) << std::endl; std::cout.flush();
//    
//    *(uint16_t *) (&answer) = *(uint16_t *) w;
//    std::cout << std::bitset<16>(answer) << std::endl; std::cout.flush();
//    
//    answer = 0;
//    *(uint8_t *) (&answer) = *(uint8_t *) w;
//    std::cout << std::bitset<16>(answer) << std::endl; std::cout.flush();
//    
//    sum = (sum >> 16) + (sum & 0xFFFF);
//    sum += (sum >> 16);
//    sum = ~sum;
//    
//    std::locale loc0;                 // copy of the current global locale
//    std::locale loc1 = std::locale(); // copy of the current global locale
//    std::locale loc2("");            // copy of ‘‘the user’s preferred locale’’
//    std::locale loc3( "C");                     // copy of the "C" locale
//    std::locale loc4 = std::locale::classic();  // copy of the "C" locale
//    std::locale loc5( "POSIX"); // copy of the implementation-defined "POSIX" locale
//    
//    printf( "name of current global locale:%s", std::locale().name().c_str());
//    printf( "name of classic C locale:%s", std::locale::classic().name().c_str());
//    printf( "name of user's preffered current locale:%s", std::locale("").name().c_str());
//    
//    std::locale loc6( "en_US.UTF-8");
//    
//    std::collate<char>* c = new std::collate_byname<char>("C");
//
//    return 0;
//}


class a
{
     int m_var;
     int m_var2;
public:
    a()
    {
        m_var=1;
        m_var2=2;
    }

    friend void set(a& obj1);
    friend void show(a ob);

};



void set( a& obj1)

{
    std::cout<<"please enter the first number"<< "\n";
    std::cin>>obj1.m_var;
    std::cout<<"please enter the second number"<<"\n";

    std::cin>>obj1.m_var2;


}
void show(a obj)
{
        std::cout<< (obj.m_var+obj.m_var2);

    }



int main()
{
    a s;

    set(s);
    show(s);
    return 0;

}