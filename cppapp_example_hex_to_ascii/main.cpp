/* 
 * File:   main.cpp
 * Author: Piotr Gregor  postmaster@cf16.eu
 *
 * Created on August 25, 2013, 7:03 PM
 */


//this works if the string chars are only 0-9A-F:

#include <stdio.h>
#include <string.h>
#include <new>
#include <bitset>

int hex_to_int(char c){
        int first = c / 16 - 3;//    1st is dec 48 = char 0
        int second = c % 16; //      10 in 1st16  in 2nd 16
        
        // decimal code of ascii char 0-9:48-57  A-E: 65-69
        // omit dec 58-64:  :,;,<,=,>,?,@
        // map first or second 16 range to 0-9 or 10-15
        int result = first*10 + second;
        if(result > 9) result--;
        return result;
}

int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}

void binary(int i) {
    std::bitset<8*sizeof(int)> b = i; // assume 8-bit byte, see Stroustrup B. "C++..." &22.2
    std::string s = b.to_string<char>();
    printf("\n%s",s.c_str());
}

#include <iostream>

void binary2(int i) {
    std::bitset<8*sizeof(int)> b = i; // assume 8-bit byte, see Stroustrup B. "C++..." &22.2
    std::cout<<std::endl<<b;
}

int main(){
        const char* st = "48656C6C6F3B";
        int length = strlen(st);
        int i;
        char buf = 0;
        for(i = 0; i < length; i++){
                if(i % 2 != 0){
                        printf("%c", hex_to_ascii(buf, st[i]));
                }else{
                        buf = st[i];
                }
        }
        binary(11);
        binary(56);
        binary2(11);
        binary2(56);
}

//struct A {
//    float m_x;
//    float m_z;
//public:
//    A(float x): m_x(x) {}
//    A(){}
//};
//
//class B : public A {
//public:
//    B(float z){
//    m_x = z;
//    }
//};
//
//int main(){
//    B b(1);
//    return 0;
//}
