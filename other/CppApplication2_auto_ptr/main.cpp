/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on February 25, 2013, 10:48 PM
 */
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <vector>
using namespace std;

#include <ql/interestrate.hpp>
#include <math.h>
#include <boost/test/unit_test.hpp>
//#include <type_traits>

float my_NaN(){
        int nan = 0x7F800001;
        return *(float*)&nan;
}

float my_inf(){
        int inf = 0x7F800000;
        return *(float*)&inf;
}

float something(){
        int inf = 0x7F7FFFFF;
        return *(float*)&inf;
}

void f(int i){std::cout<<i<<",";}

class A{
public:
    ~A(){std::cout<<"karramba!";}
    char* c;
    A():c("KK"),i_(123){}
    void init(){
        static const int a2 = 0;
        a1=a2;
    }
    int i(){return i_;}
    A const& operator+=(int i){
        std::cout<<"operator+=";
        this->i_=i_+i;
    }
    A const& operator<<(int i){
        this->i_=123;
        return *this;
    }
    void what(){std::cout<<"what!";}
    void what()const{std::cout<<"whatconst!";}
private:
    static int a1;
    int i_;
};
    void gwhat(A& a){std::cout<<"what!";}
    void gwhat(A const& a){std::cout<<"whatconst!";}
    void hwhat1(A& a){std::cout<<"what!";}
    void hwhat2(A const& a){std::cout<<"whatconst!";}
    
int A::a1=0;
template<class T>
T templatefunc_1(T t){return 2*t;}

template<class T,class U>
U templatefunc_2(T t){}

template <typename T, typename U>
void _new_func(U(*func)(T)) {
}

template <typename T>
    class ArrayDeleter
    {
    public:
        void operator () (T* d) const
        {
            delete [] d; //will delete array!
        }
    };
    
    
typedef enum {a,b,c,d} EnumType;

template <typename Type>
class Foo
{
public:
    //Foo() {}  // <---- "Member 'b' was no initialized in this constructor"

public:
    Type a;
    EnumType b;
};

class B 
{
public:
    static const int a = 0;
};

/*
 * 
 */
int main(int argc, char** argv) {
    
    A a1;
    a1+=3;
    std::cout<<a1.i();
    a1<<100;
    std::cout<<a1.i();
    a1.what();
    const A a2;
    a2.what();
    gwhat(a1);
    gwhat(a2);
    
    hwhat1(a1); //OK
    hwhat2(a1); //OK
    //hwhat1(a2); //error
    hwhat2(a2); //OK
    
    Foo<int> fo;
    std::cout<<std::endl<<"fo.a:"<<fo.a<<",fo.b:"<<fo.b<<std::endl;
    EnumType e=d;
    fo.b=d;
    std::cout<<std::endl<<"fo.a:"<<fo.a<<",fo.b:"<<fo.b<<std::endl;
    
    Foo<int>* go=new Foo<int>;
    std::cout<<std::endl<<"go->a:"<<go->a<<",go->b:"<<go->b<<std::endl;
    go->b=d;
    std::cout<<std::endl<<"go->a:"<<go->a<<",go->b:"<<go->b<<std::endl;
    
    int i_tab[10];
    i_tab[0]=1;
    i_tab[1]=2;
    
    //! initialilzation!
    int* tab1=new int[10]; //elements not initialized
    int* tab2=new int[100]();//elements guaranteed to be Default Initialized
    //and in case of POD it is Zero Initiallization
    
    int* i_tab_heap=new int[60]();
    i_tab_heap[1]=100;
    std::for_each(i_tab_heap,i_tab_heap+60,f);
    std::sort(i_tab_heap, i_tab_heap+60);
    std::for_each(i_tab_heap,i_tab_heap+60,f);
    cout<<"\n";
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
//        A* a_tab_i_dupa=new A[100];
//        boost::shared_ptr<A> a_tab_ok(a_tab_i_dupa,ArrayDeleter<A>()); //shared_ptr CAN manage array if
        //appropriate Deleter is provided !!!!!!!!!!!! 
        //alternatively:
        A* a_tab_i_dupa2=new A[4];
        boost::shared_array<A> a_tab_ok2(a_tab_i_dupa2);
    }
        A* a_tab_i_dupa2=new A[10];
        boost::shared_array<A> a_tab_ok2(a_tab_i_dupa2);
        cout<<a_tab_ok2[1].c;
        a_tab_i_dupa2=NULL;
        cout<<"\na_tab_i_dupa2 not deleted though pointer is not referenced, shared_ptr reference it yet and will delete it, but later!\n";
        //cout<<a_tab_i_dupa2[1].c;
//    boost::shared_ptr<A> b_ptr(new A());
//    //a_tab_ok->~A();
//    //std::auto_ptr<A> a_tab_ok(new A[100]);//this is wrong: new[] but will be deleted by delete
//    //not by delete[] -> Segmentation fault
//    std::vector<A> a_vec(100);
 //  A* a_ptr=new A();
//    std::auto_ptr<A> a_aptr(a_ptr);
//    // programmer error
//    std::auto_ptr<A> a2_aptr(a_ptr); // ooops! SIGABRT received !
//    QuantLib::InterestRate* qr=new QuantLib::InterestRate();
//    QuantLib::Real r=2.3;
//    
//    std::cout<<std::endl<<"nan: "<<my_NaN()<<std::endl<<"inf: "<<my_inf()<<std::endl;
//    std::cout<<std::endl<<"something: "<<something()<<std::endl;
//    BOOST_MESSAGE( "c" );
//    int (*i_ptr)(int);
//    i_ptr=&templatefunc_1<int>;
//    _new_func(&templatefunc_1<double>);
//    _new_func(&templatefunc_2<double,int>);
    return 0;
}

