/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on April 7, 2013, 4:06 PM
 */

#include <cstdlib>
using namespace std;
#include <cstdio>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <initializer_list>
#include <set>

const int a = 98;
//
void f()
{
    const int a = 99;
    const int *p = &a;
    printf("constant's value: %d\n", *p);
}
class U{
    static int count;
    int i_;
private:
    std::vector<int> v;
    std::string s;
    boost::shared_ptr<int> iptr;
public:
    U(){}
    U(int i) : i_(i) {cout << "consting " << i_ << endl;}
    U(const U& ot) : i_(ot.i_) {cout << "copying " << i_ << endl;}
};
//size_type
//      max_size() const throw() 
//      { return size_t(-1) / sizeof(_Tp); }
std::vector<string> inputVector;
void splitArguments() {

    char* args[20];

    int inputVectorIdx = 0;
    int currentArgsIdx = 0;
    int startingArgsIdx = 0;

    while (inputVectorIdx < inputVector.size()) {

        if (inputVector[inputVectorIdx] == ";") {
            for (int k = startingArgsIdx; k <= currentArgsIdx; k++) {
                cout << args[k];
            }
            startingArgsIdx = currentArgsIdx + 1;
        }

        else {
            args[currentArgsIdx] = 
                const_cast<char*>(inputVector[inputVectorIdx].c_str());
        }

        inputVectorIdx++;
        currentArgsIdx++;
    }
}
class A
{
protected:
    A* parent;
};

class B : public A
{
public:
    B(void){parent = new B;}
    ~B(void){delete parent;}
protected:
    int a;
    void f(void){ printf("%d",a);}
};

class C : public B
{
    //void ff(void){ printf("%d",((parent)->a)); }
};



int main(int argc, char** argv)
{
    //std::vector<int> vi;
    //int i_j=vi[0];
    //printf("v[0]:%d",vi[0]);
    
    std::vector<U> arr(2,U(3));
    arr.resize(4);
    //C* c=new C();
    //c->f();
    int myints1[]= {10,20,30,40,50};
    int myints2[]= {50,40,30,20,10};
    std::set<int> s1 (myints1,myints1+5);
    std::set<int> s2(myints2,myints2+5);
    if(s1==s2){
        printf("sets: true");
    }else printf("sets: false");
    std::set<int>::iterator it2=s2.begin();
    for(std::set<int>::iterator it1=s1.begin();it1!=s1.end();it1++){
                printf("\ns1: %d  s2: %d",*it1,*it2);
        it2++;
    }
    
    inputVector.push_back("/bin/echo");
    inputVector.push_back("was");
    inputVector.push_back("here");
    inputVector.push_back(";");
    inputVector.push_back("somethin");
    inputVector.push_back("g");
    inputVector.push_back(";");
    inputVector.push_back("OK");
    inputVector.push_back(";");
    splitArguments();
    //vector<U> v1 = {U(1),U(2),U(3),U(4)};
    //vector<U> v2(1,U(15));
    int array[10]={0};
    for (int i = 10; --i>= 0; )
        {
        printf("arr[%d]:%d",i,array[i]);
        }
    const int& iref=int(3);
    int a= iref;
    printf("iref: %d\n", a);
    
    int B[20]={1};
    int* A=new int[20];
     int b=100;
     f();
//     int c = 101;
//     const int d=102;
//     const int* p_d=&c;
//     int* p_b=&b;
//     printf("%d",*p_b);
//     int i=164;
//     printf("%d",*p_d);

//    printf("global const: %d\n", a);
//    f();
//    printf("local const: %d\n", c);
    return 0;
}


