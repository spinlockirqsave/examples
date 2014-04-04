/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on March 13, 2013, 1:20 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include <stdio.h>
#include <string.h>
//#include <boost/pool/pool.hpp>
#include <fstream>
#include <memory>
/*
 * 
 */
void f(const char* c){
    cout<<"\n<<<<"<<&c<<">>>"<<"<<<<"<<*c<<">>>\n";
    printf("<<<%p>>><<<%p>>>",&c,c);
}

class CComplex{
public:
    CComplex(int real1,int image1,char c)
    {
        cout<<"RealImg";
        real=real1;
        image=image1;
        char* x; char xc=c;x=&xc;
        void* v;
        f(x);
        CComplex ccc(x,v);
        CComplex cccc(1,2,3);
    }
    CComplex():real(0),image(0){cout<<"DEFAULT";}
    CComplex(const CComplex &c)
    {
        real=c.real;
        image=c.image;
        cout<<"COPY";
    }
    CComplex& operator=(CComplex const& ref){ 
        cout<<"ASSIGN";
        //CComplex* c;
        CComplex cobj(43,45,'x');
        //c=&cobj;
        //CComplex* c=new CComplex(44,45); 
        return cobj;
    }
    
    CComplex(int i1, int i2, int i3){cout<<"\n123!";}
    CComplex(const char* y,void* v){cout<<"\nCrefvoid!";}
    ~CComplex(){cout<<"\n~CComplex(){}";}
public:
    void Display(void)
    {
        cout<<real<<"+"<<image<<"i"<<endl;
    }
    static bool CComplexComparator(CComplex c1, CComplex c2){return true;}
    static void CComplexInit(CComplex& c){
        c.real=100;
    }
    int real,image;
};

//void CComplexInit(CComplex& c){
//    //CComplex tmp(1,2);
//}
//bool CComplexComparator(CComplex c1, CComplex c2){return true;}
bool intComparator(int i1, int i2){return true;}
void intInit(int& i){i=100;}

CComplex& fC(void){cout<<"\n:fC:";CComplex* c=new CComplex(9,9,'y');return *c;}


class Foo
{
public:
    static int m;
static void Setm(int i) { m = i; }
private:
};
int Foo::m=2;


class Bar
{
 public:
     int m_;
 Bar(int m):m_(m) {Foo::Setm(m);}
 Bar(){}
 void what(){cout<<"\n->"<<m_<<endl;}
 ~Bar(){cout<<"\n->~"<<m_<<endl;}
 void f();
};

class SBar{
public: 
    SBar(){}
    int m;
    char c;
    vector<int> v;
    string d;
};

char* XOR(string s, int key){
 string res = "";
 for (size_t temp = 0; temp < s.size(); ++temp){
  res += s[temp] ^ ((key + temp) % 255);
 }
 char * cstr = new char [res.length()+1];
 //strcpy (cstr, res.c_str());
 copy(res.begin(),res.end(),cstr);
 return cstr;
}

char XORchar(const string &s, int key){
    char res = 0;
    for (size_t temp = 0; temp < s.size(); ++temp){
        res += s[temp] ^ ((key + temp) % 255);
    }
    return res;
}
typedef void handler_t(int);


class foo{
   private: 
      int* array;
   public:
      foo(int i):array(new int[i]){}
};

int main(int argc, char** argv) {

    int low=2, high=3;
    float ff=2.0f;
    float fff=ff/3;
    float t=(float)rand()/RAND_MAX;
    float f=(1.0f-t)*low+t*high;
    
    cout<<"\n-------\n";
    
    CComplex c1(10,20,'1');
    CComplex c2(0,0,'2');
    c1.Display();
    c2.Display();
    c2=c1;
    c2.Display();
    
    vector<CComplex> cv(1000,CComplex());
    for_each(cv.begin(),cv.end(),CComplex::CComplexInit);
    sort(cv.begin(),cv.end(),CComplex::CComplexComparator);
    cout<<"\ncv.size():"<<cv.size();
    
    vector<int> iv;
    for_each(iv.begin(),iv.end(),intInit);
    sort(iv.begin(),iv.end(),intComparator);
    
    CComplex cf=fC();
    
    Foo::Setm(5);

    
    printf("]n---------------------------------------------\n");
    //char s[] = "asd";
    //char* p = &s[0];
    //char** pp=&p;
    char* s = "asd";
    char** p = &s;
    
    printf("The value of s is: %p\n", s);
    printf("The direction of s is: %p\n", &s);

    printf("The value of p is: %p\n", p);
    printf("The direction of p is: %p\n", &p);

    printf("The direction of s[0] is: %p\n", &s[0]);
    printf("The direction of s[1] is: %p\n", &s[1]);
    printf("The direction of s[2] is: %p\n", &s[2]);

    string es("stringins");
    cout<<endl;
    cout<<XOR(es,3);cout<<endl;
    cout<<XOR(es,4);cout<<endl;
    
    string resp4=XOR(es,4);
    cout<<resp4;cout<<endl;
    char resp4c=XORchar(es,4);
    cout<<resp4c;cout<<endl;
    string resp3=XOR(es,3);
    cout<<resp3;
    //Bar bar(1009);
    //Bar* b_ptr=&bar;
    //b_ptr->what();
    //b_ptr->~Bar();
    //b_ptr->what();
    
    handler_t h;
    
    char c='A';
    int cToi=c;
    cout<<"\nc:"<<c<<"\tcToi:"<<cToi<<endl;
    
    c='4';
    cToi=c;
    cout<<"\nc:"<<c<<"\tcToi:"<<cToi<<endl;
    
    c='0';
    cToi=c;
    cout<<"\nc:"<<c<<"\tcToi:"<<cToi<<endl;
    
    c='\0';
    cToi=c;
    cout<<"\nc:"<<c<<"\tcToi:"<<cToi<<endl;
    
    c=0;
    cToi=c;
    cout<<"\nc:"<<c<<"\tcToi:"<<cToi<<endl;
    
    int ic=65;
    char iToc=ic;
    cout<<"\nic:"<<ic<<"\tiToc:"<<iToc<<endl;
    ic=48;
    iToc=ic;
    cout<<"\nic:"<<ic<<"\tiToc:"<<iToc<<endl;
    ic=10;
    iToc=ic;
    cout<<"\nic:"<<ic<<"\tiToc:"<<iToc<<endl;
    ic=7;
    const char* iTocc=(const char*)&ic;
    cout<<"\nic:"<<ic<<"\tiToc:"<<iTocc<<endl;
    
//    ofstream myfile;
//    myfile.open ("print_chars.txt");
//    for(int i=0;i<128;i++){
//        char c=i;
//        myfile<<"i:"<<i<<", char:"<<c<<"\n";
//    }
//
//    myfile.close();
  
    //char ctab[4];//'Aa 4'?
    char* ctab=new char[4];
    ic=65;//'A'
    iToc=ic;
    ctab[0]=iToc;
    ic=0;//'NUL'
    iToc=ic;
    ctab[1]=iToc;
    ic=33;//!
    iToc=ic;
    ctab[2]=iToc;
    ic=52;//'4'
    iToc=ic;
    ctab[3]=iToc;
    
    cout<<endl;
    cout<<ctab<<endl<<ctab[0]<<ctab[1]<<ctab[2]<<ctab[3]<<endl;
    cout<<ctab[0]<<endl;
    cout<<ctab[1]<<endl;
    cout<<ctab[2]<<endl;
    cout<<ctab[3]<<endl;
    cout<<ctab[0]<<endl;
    cout<<ctab[1]<<endl;
    cout<<ctab[2]<<endl;
    cout<<ctab[3]<<endl;
    
    Bar y;
    y.what();
    Bar b(5);
    b.what();
    //b.f();
    
    SBar* b1=new SBar;
    SBar* b2=new SBar();
    cout<<"\nSBar:"<<b1->m;
    cout<<"\nSBar():"<<b2->m;
    
    
    return EXIT_SUCCESS;
}
void Bar::f(){cout<<"\n\n----\nbar.f()\n-----\n\n";}
