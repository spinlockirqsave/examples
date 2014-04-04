/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on April 15, 2013, 8:56 PM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;

/*
 * 
 */
class A{int i; public: static int integer(){return 100;}};
class AA{
public:
    AA(){}
    AA(const AA&){}
    AA& operator=(const AA& other){
        return *this;
    }
    
};
struct MixedData //MixedData size: 12
{
    char Data1;
    short Data2;
    int Data3;
    char Data4;
};
struct MixedDataPaddingExplicit  /* After compilation in 32-bit x86 machine, MixedDataPaddingExplicit size: 12 */
{
    char Data1; /* 1 byte */
    char Padding1[1]; /* 1 byte for the following 'short' to be aligned on a 2 byte boundary 
assuming that the address where structure begins is an even number */
    short Data2; /* 2 bytes */
    int Data3;  /* 4 bytes - largest structure member */
    char Data4; /* 1 byte */
    char Padding2[3]; /* 3 bytes to make total size of the structure 12 bytes */
};

struct MixedDataOptimalPadding  /* after reordering (now no padding), MixedDataOptimalPadding size: 8 */
{
    char Data1;
    char Data4;   /* reordered */
    short Data2;
    int Data3;  
};

#include <iostream>
#include <cmath>
#include <stdlib.h>    
#include <vector>
bool isPrime(char myArr[])
{
    int myInt=atoi(myArr);
    int maxX=sqrt(myInt)+1;
    for(int x=0; x<maxX; x++)
    {
        if(!myInt%x)
            return false;
    }
    return true;
}

int main(int argc, char** argv) {
    srand(1629);
    int output = ((double)rand()/(double)RAND_MAX)*1000;
    cout<<"output: "<<output<<"\n";
//    A aq;
//    int u=aq.integer();
    //printf("A size: %d",sizeof(a));
    AA aa;
    printf("AA size: %d",sizeof(aa));
    printf("Pointer size: %d",sizeof(int*));
    
    MixedData m1;
    MixedDataPaddingExplicit m2;
    MixedDataOptimalPadding m3;
    printf("\nMixedData size: %d",sizeof(m1));
    printf("\nMixedDataPaddingExplicit size: %d",sizeof(m2));
    printf("\nMixedDataOptimalPadding size: %d",sizeof(m3));
    

    
    //this vector will store the integers
    vector<int> a;
    // this will store the user input
    string inp;
    getline(cin, inp);
    // this string will temporarily store the digits
    string tmp;
    //be sure that the reading part is okay
    cout << inp << endl;
     //until you meet something different than a digit, read char by char and add to string
     for(int i = 0; i < inp.length(); i++)
    {
        if(isdigit(inp[i]))
        {
            tmp =inp[i];
            int value = atoi(tmp.c_str());
            a.push_back(value);
        }
        else
        {
            tmp = "";
        }
    }
    // paste the entire vector of integers
    for(int i = 0; i < a.size(); i++)
    {
        cout << a[i] << endl;
    }
    return 0;
    
    return 0;
}

