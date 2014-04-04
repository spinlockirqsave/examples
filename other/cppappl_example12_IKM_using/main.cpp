/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on April 25, 2013, 10:59 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <memory>
#include <istream>
//using namespace std;

class Port{
protected:
    bool D;
    bool CLK;
    bool Q;
    bool QN;
public:
    virtual void architecture_behavior();
    virtual void setD(bool input);
    virtual void setCLK(bool clk);
};

class Dflipflop : public Port{
public:
    Dflipflop(bool clk, bool d){
        CLK=clk;
        D=d;
    }
    void architecture_behavior(){
        if(CLK=true){
            Q=D;
            QN=!Q;
        }
    }
    void setD(bool d){
        D=d;
    }
    void setCLK(bool clk){
        CLK=clk;
    }
    bool state(){
        return Q;
    }
};

class Dflipflop2 : public Port{
public:
    Dflipflop2(bool clk, bool d){
        CLK=clk;
        D=d;
    }
    void architecture_behavior(bool d, bool clk){ // set state
        D=d;
        if(CLK=true && clk==false){
            Q=D;
            QN=!Q;
        }
        CLK=clk;
    }
    bool state(){
        return Q;
    }
};

class A{
    void a(){}
    virtual  void a2()=0;
};

class B : public A{
public: 
    void a(){
        
    }
    void a2(){}
    int i;
};
/*
 * 
 */
int key=100;
char op(char c){
    char letter = c;
        int val = (int)letter; // getting ascii value of each letter.
        int EnVal = (val - 32) + key;
            if(EnVal > 95)
            {
                EnVal = (EnVal - 95) + 32;

            }
        char EnLetter = static_cast<char>(EnVal);
        return EnLetter;
}

class U{
public:
    int a;
protected:
    int b;
private:
    int c;
};

class V : private U{
public:
    using U::b;
    using U::a;
};

typedef std::unique_ptr<int> myType;

class myClass{

    myType myStream;
public:

    myClass(myType a_stream){
        myStream = std::move(a_stream);
    }

};

int main(int argc, char** argv) {

//    std::vector<int> v;
//    B b;
//    b.a();
//    if("r"=="s" || "e"){
//        printf("true\n");
//    }
//    
//    std::string s="piotrek";
//    std::vector<char> vc_in(s.begin(),s.end());
//    std::vector<char> vc_out;
//    std::transform (vc_in.begin(), vc_in.end(), std::back_inserter(vc_out), op);
//    
//    std::copy(vc_out.begin(), vc_out.end(),std::ostream_iterator<char> (std::cout,"_"));
    
    char a[]="Ansi C";
    char* bb="Ansi C";
    printf("%d %d",sizeof(a),strlen(bb));
    
    int r=0;
    int arr[3][4]={1,2,3,4,4,3,2,1,7,8,9,0};
    
    printf("%u  %u",arr,(arr+1));
    short int si=0;
    long int li=0;
    int s1=sizeof(si);
    int s2=sizeof(li);
    
    V v;
    printf("\nV: %d %d %d",v.a,v.a,v.b);
    
    U u;
        printf("\nU: %d %d %d",u.a,u.a,u.a);
        
    std::unique_ptr<int> unptr(new int());
    std::cout << "unptr: " << (unptr?"not null":"null") << '\n';
    printf("-std=c++0x unique_ptr points to: %d",*unptr);
        
    
    return 0;
}

