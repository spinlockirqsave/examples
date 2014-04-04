/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on February 16, 2013, 3:40 AM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
//using namespace std;

/*
 * 
 */
int get_length(const char* c){
    int i=0;
    while(!(*c=='\0')){
        i++;
        std::cout<<*c++;
    }
    return i;
}

template<typename T, size_t N>
T* end(T (&ra)[N]) {
    return ra+N;
}

int main(int argc, char** argv) {
    char* c_ptr=NULL;
    char c_tab[]={'s','t','r','i','n','g'};
    std::vector<char> v(c_tab,end(c_tab));
    //v.push_back(c_tab);
    std::string s="string"; 
    //std::string s2={"a"};
    std::cout<<"calling get_length(char tab[]) below:"<<std::endl;
    int i = get_length(s.c_str());
    std::cout<<std::endl<<"end. length returned="<<i<<std::endl<<std::endl;
    
    for(std::vector<char>::iterator it=v.begin(); it!=v.end(); it++){
        std::cout<<"="<<*it<<std::endl;
    }
    std::cout<<std::endl<<"sizeof(char)="<<sizeof(char)<<std::endl;
    std::cout<<"sizeof(int)"<<sizeof(int)<<std::endl;
    std::cout<<"sizeof(double)"<<sizeof(double)<<std::endl;
    std::cout<<std::endl<<"sizeof(char*)="<<sizeof(char*)<<std::endl;
    std::cout<<"sizeof(int*)"<<sizeof(int*)<<std::endl;
    std::cout<<"sizeof(double*)"<<sizeof(double*)<<std::endl;
    return 0;
}

