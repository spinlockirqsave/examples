/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on March 28, 2013, 5:46 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;
#include <cstring>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <algorithm>
#include <stdio.h>

class A{
    public:
        static int i_;
    string name_;
    virtual void step1(){cout<<"A: step1"<<endl;}
    void step2(){cout<<"A: step2"<<endl;}
    virtual void step3(){cout<<"A: step3"<<endl;}
    void step4(){cout<<"A: step4"<<endl;}

    void algorithm(){
        cout<<"A: algorithm"<<endl;
        step1();
        step2();
        step3();
        step4();
    }
    A(){}
    A(string name):name_(name){}
    ~A(){cout<<"~A"<<name_;}
private:
    virtual void privatef(){cout<<"A:pf";}
    static int hiden_i_;
protected:
    virtual void protectedf(){cout<<"A:protectedf";}
};
int A::i_;

class B: public A{
public:
    void step1(){cout<<"B: step1"<<endl;}
    void step2(){cout<<"B: step2"<<endl;}
    virtual void step4(){cout<<"B: step4"<<endl;}
private:
    void privateg(){protectedf();} //protected base class function can be called only
    //inside the class from which it derive
};

class AA{
    public:
    string name_;
    virtual void pstep1(){cout<<"AA: pstep1"<<endl;}
    void pstep2(){cout<<"AA: pstep2"<<endl;}
    virtual void pstep3(){cout<<"AA: pstep3"<<endl;}
    void pstep4(){cout<<"AA: pstep4"<<endl;}
    void pstep5(){cout<<"AA: pstep5"<<endl;}
    void pstep6(){cout<<"AA: pstep6"<<endl;}

    void algorithm(){
        cout<<"AA: algorithm"<<endl;
        step1();
        step2();
        step3();
        step4();
    }
    AA(){}
    AA(string name):name_(name){}
     virtual ~AA(){cout<<"~AA"<<name_;}
private:
    virtual void step1(){cout<<"AA: step1"<<endl;}
    void step2(){cout<<"AA: step2"<<endl;}
    virtual void step3(){cout<<"AA: step3"<<endl;}
    void step4(){cout<<"AA: step4"<<endl;}
    void step5(){cout<<"AA: step5"<<endl;}
    virtual void privatef(){cout<<"AA:pf";}
    virtual void pstep6private(){cout<<"AA: pstep6private"<<endl;}
protected:
    virtual void protectedf(){cout<<"AA:protectedf";}
};

class BB: public AA{
public:
    void pstep1(){cout<<"BB: pstep1"<<endl;}
    void pstep2(){cout<<"BB: pstep2"<<endl;}
    virtual void pstep4(){cout<<"BB: pstep4"<<endl;}
    
    void step1(){cout<<"BB: step1"<<endl;}
    void step2(){cout<<"BB: step2"<<endl;}
    virtual void step4(){cout<<"BB: step4"<<endl;}
    virtual ~BB(){cout<<"~BB"<<name_;}
private:
    void privateg(){protectedf();} //protected base class function can be called only
    //inside the class from which it derive
};
class CC{
public:
    static CC* cObj(){
        if(c_ptr==NULL){
            return new CC();
        }else return c_ptr;
    }
    int getValue(){return value_;}
    void setValue(int val){value_=val;}
    ~CC(){cout<<"~CC";}
private:
    CC():value_(12345){cout<<"CC";}
    static CC* c_ptr;
    //~CC(){cout<<"~CC";}
    int value_;
protected:
    //~CC(){cout<<"~CC";}
};
// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
CC *CC::c_ptr = 0;

class CC2{
public:
    static CC2& cObj(){
        static CC2 c_(12345);
        //this way singleton is deleted on program exit
        return c_;
    }
    //int getValue(){return CC2::c_.value_;}
    //void setValue(int val){value_=val;}
    ~CC2(){cout<<"~CC2";}
private:
    CC2():value_(12345){cout<<"CC2";}
    CC2(int i):value_(i){cout<<"CC2i";}
    int value_;
    CC2(const CC2& c){}
    CC2 operator=(const CC2& c){}
    //static CC2& c_;
    static bool created;
protected:
};
bool CC2::created=false;
/*
 * 
 */
struct position {
 int x;
 int y;
};


        class Event
        {
            public:
                // Class Variable
                int Measure;
                int Beat;
                int Position;

                // This Class that was I mean
                class SampleEvent;
                class TimeEvent;
                virtual void f(){}
                // Constructor
                Event(int measure, int beat, int pos);
                Event(){}
        };

        // Sample Event Class (inherit to Event Class)
        class SampleEvent : public Event
        {
            public:
            // variable in SampleEvent Class
            int ID;
            float Pan;
            float Vol;

            // Constructor
            SampleEvent(int id, float pan, float vol, int measure, int beat, int pos);
            SampleEvent(){}
        };

        // Time Event Class (inherit to Event class)
        class TimeEvent : public Event
        {
            public:
            // variable in TimeEvent Class
            double Value;

            // Constructor
            TimeEvent(double value, int measure, int beat, int pos);
            TimeEvent(){}
        };
namespace MyStr{    
class Str
{
private:
    unsigned int length;
    char *data;
public:
    Str(){}
    Str(const Str&){}
    Str(const char*){}
    Str(char c, unsigned int db){}
    //lots of irrevelant functions here...
    friend int operator/ (const Str&, char);
    friend std::ostream& operator<< (std::ostream&, const Str&);
};
}
namespace MyStr{  
ostream& operator<< (ostream& out,const Str& str)
{
    for (int i=0; i<str.length; i++)
    {
        out<<str.data[i];
    }
    out<<endl;
    return out;
}

int operator/ (const Str& str, char c)
{
    for (int i=0; i<str.length; i++)
    {
        if(str.data[i]==c) return i;
    }
    return -1;
}
}

void add_1(const double& x)
{ //x += 1.0; }
}
int f1(){int* iptr=new int[5];return *iptr;}
int* f2(){return new int[5];}
//int* z(){int* iptr=new int[5];return iptr;}
int (*z())[5];//{int* ptr=new int[5];return ptr;}
typedef int int5[5]; // simplify syntax later on
int5* z() {
   int (*array_ptr)[5]; 
   int* itab=new int[5];
   (*array_ptr)[0]=0;
   return array_ptr;
}

class Aa {
public:
    Aa();
};

class Bb {
public:
    Bb();
};

Aa::Aa(){
    new Bb;//do something
}
Bb::Bb(){
    new Aa;//do something
}
template<typename T>
bool myCompare(const T& x, const T& y)
        {return *x < *y;}

class withDctor{
public:
    int i;
    withDctor(){}
    withDctor(withDctor const& c){}
    ~withDctor(){}
};
class withoutDctor{
public:
    int i;
    withoutDctor(){}
};

struct NameContainer{
char name [32];
};

inline bool operator== (const NameContainer &first,const NameContainer &second){
        return (strcmp(first.name,second.name)==0);
    }

struct NameContainer2{
    string name;

    bool operator==(string str) {
        return name == str;
    }
};

struct DD {
  DD() {}
  DD(const DD&) { std::cout << "Hello World!\n"; }
};
 
void f() {
  DD d;
  throw d; // copying the named object c into the exception object.
}          // It is unclear whether this copy may be elided.

int n = 0;
struct C {
    int i;
  C(int) {}
  C(const C&) { ++n; } // the copy constructor has a visible side effect
};                     // it modifies an object with static storage duration

void g1( C const & ref ){
 C copy(ref);
 copy.i=1;
// operate on copy // operate on arg
}
void g2( C arg ){
    arg.i=1;
// operate on copy // operate on arg
}
C g3(C arg){
    return arg;
}
#include <exception>
extern "C" void fo() {throw std::exception();}

int main(int argc, char** argv) {

    g1(C(8));
    std::cout << n << std::endl; //prints 1 because of 1 copy in g1 body
    n=0;
    
    g2(C(7));
    std::cout << n << std::endl; //prints 0 because copy on rvalue C() is omitted
    n=0;
    
    g2(g3(C(7)));
    std::cout << n << std::endl; //prints 1 because copy of g3 func result to g2 arg cannot be omitted
    n=0;
    //coclusion: copy rvalue (temporary) is omitted (eluded) but func result copy cannot be omitted
    //because calling convention defines memory location to put there result of func and ANOTHER 
    //location as argument creation !
    try {
    f();
  }
  catch(DD c) {  // copying the exception object into the temporary in the exception declaration.
      cout<<"catched"; 
  }             // It is also unclear whether this copy may be elided.
    
        C c1(42); // direct-initialization, calls C::C(42)
        C c2 = 42; // copy-initialization, calls C::C(42) _or_ C::C( C(42) )
        std::cout << n << std::endl; //prints 0 if the copy was elided, 1 otherwise
  
    NameContainer* _storedNames = new NameContainer[1];
    std::vector<NameContainer> vn(_storedNames, _storedNames + 1);
    const char* cc="piotr";
    NameContainer nc;
    memcpy(nc.name,cc,strlen(cc)+1);
    vn.push_back(nc);
    NameContainer myObjectPredicate;
    memcpy(myObjectPredicate.name,cc,strlen(cc)+1);
    int count=std::count(vn.begin(), vn.end(), myObjectPredicate);
    
    NameContainer2* _storedNames2 = new NameContainer2[1];
    std::vector<NameContainer2> vn2(_storedNames2, _storedNames2 + 1);
    std::cout << std::count(vn2.begin(), vn2.end(), "poul");    
    withoutDctor w;
    withoutDctor w2;
    w2=w;
    withDctor ww;
    withDctor ww2;
    ww2=ww;
    
    int i1=11;
    int i2=12;
    int iref1=i1;
    int iref2=i2;
    //bool boo=myCompare(i1,i2);//error: invalid type argument of ‘unary *’
    int* iiptr=&i2;
    bool boo=myCompare(&i1,iiptr);//ok
    int(* ipptr)[5]=0;
    ipptr=z();
    int i=0;
    add_1(i);
    cout<<"i:"<<i;
    //Singleton pattern
    CC* myC = CC::cObj();
    cout<<myC->getValue();
    CC2& cC2singleton=CC2::cObj();
    
    //boost::shared_ptr<CC> bCptr(CC::cObj());
    //CC c;
    AA aa;
    BB bb;
    bb.algorithm();
    bb.pstep1();
    bb.::AA::pstep1();
    bb.pstep2();
    bb.::AA::pstep2();
    bb.pstep3();
    bb.pstep4();
    bb.pstep5();
    AA* bbptr=&bb;
    bbptr->AA::pstep1();
    bbptr->pstep2();
    bbptr->pstep3();
    bbptr->pstep4();
    bbptr->pstep5();
    
    //bb.~BB();
    AA* BBptr=new BB();
    delete BBptr; // ~AA must be virtual to avoid leak here
    
    A a;
    B b;
    a.algorithm();
    b.algorithm();
    B* bptr=&b;
    bptr->algorithm();
    A* aptr=&b;
    aptr->algorithm();
    
    A* a1=new A("a1");
    A* a2=new A("a2");
    delete a1, a2;
    cout<<"\n----\n";
    delete a2, a1;
    
    b.step2();
    bptr->step2();
    aptr->step2();
    
    char ctab[5];
    strncpy(ctab, "pcs", sizeof(ctab)); 
    
    cout<<ctab;
    
    map<int,int> m;
    position p{1,7};
    m.insert(std::pair<int,int>(p.x,p.y));
    
    map<int,position> ip;
    position pos{1,8};
    std::pair<int,position> pair=std::make_pair<int,position>(1,pos);
    ip.insert(pair);
    
    SampleEvent* SE = new SampleEvent();
    TimeEvent* TE = new TimeEvent();
    std::vector<Event* > DataEvent;

    //insert Event
    DataEvent.push_back(SE);
    DataEvent.push_back(TE);
    
    SampleEvent* te_ptr=dynamic_cast<SampleEvent* >(DataEvent[0]);

    MyStr::Str s;
    cout<<s;

    return 0;
}

