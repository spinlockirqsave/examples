/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on April 25, 2013, 6:21 PM
 */

#include <cstdlib>
#include <cstdio>
#include <string>
#include <exception>
#include <list>
#include <vector>
#include <iterator>
#include <typeinfo>
class A{
    std::string name_;
public:
    A(std::string name):name_(name){}
    ~A(){
        if(std::uncaught_exception()){
            printf("~A -> stack unwinding %s\n",name_.c_str());
        }else{
            std::printf("~A -> common destruction %s\n",name_.c_str());
        }
    }
};

class B{
        std::string name_;
        A a;
public:
    B(std::string name):name_(name),a(name){}
    ~B(){
        if(std::uncaught_exception()){
            printf("~B -> stack unwinding %s\n",name_.c_str());
        }else{
            printf("~B -> common destruction %s\n",name_.c_str());
        }
    }
};

class myErr : public std::exception{
public:
    myErr()throw(){}
    ~myErr()throw(){}
    virtual const char* what() const throw() {
        return "myErr exception";
    }
//  virtual const char* what() const throw()
//  {
//    return "My exception happened";
//  }
};

void f(){
        try{
        A a2("a2");
        throw myErr();
    }catch(std::exception& e){
        //printf("%d",e);
        printf("%s",e.what());
    }
}

void g(){
        try{
        B b1("b1");
        throw myErr();
    }catch(std::exception& e){
        //printf("%d",e);
        printf("%s",e.what());
    }
}
/*
 * 
 */
int main(int argc, char** argv) {

//    {
//        A a1("a1");
//    }

    f();
    printf("\n-------------------\n");
    g();
    
    std::list< std::vector<int> > li;
    li.push_back(std::vector<int>());
    li.push_back(std::vector<int>());
    std::vector<int> v3(3);
    v3.push_back(1);
    v3.push_back(2);
    v3.push_back(3);
    li.push_back(v3);
     for (std::list<std::vector<int> >::iterator it1 = li.begin(); it1 != li.end(); ++it1){
     std::vector<int>::iterator it2;
     for (it2 = (*it1).begin(); it2 != (*it1).end(); ++ it2){
          //do something with vec_it
          //for example call member function of Class
          printf("element: %d\n",(*it2));
     }
     }

//    std::list< std::vector<int> > li2;
//
//    li2.push_back({1, 2, 3}); //push_back vector
//    li2.push_back({4, 2, 6}); //again, vector implicitly
//
//    for (auto& vv : li2) {
//        for (auto &i : v)
//            printf("element: %d\n", 8);
//        
//    }
    
    return 0;
}


