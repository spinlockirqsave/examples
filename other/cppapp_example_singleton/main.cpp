/* 
 * File:   main.cpp
 * Author: peter@
 *
 * Created on August 25, 2013, 3:39 PM
 */

#include <cstdlib>
#include <cstdio>
using namespace std;

/*
 * 
 */
//header============================================
#include <iostream>
using namespace std;
 
class singleton
{
public:
        static singleton* getInstance();
        static singleton* getInstance(int wIn,int lIn);
        static void terminate();// memmory management
        int getArea();// just to test the output
 
 
private:
        static bool flag;
        singleton(int wIn, int lIn);
        singleton();
        static singleton* single;
        int width,len;
};
 
int singleton::getArea(){
        return width*len;
}

singleton* singleton::getInstance(int wIn,int lIn){
 
        if (!flag)
        {
                single= new singleton(wIn,lIn);
                flag= true;
                return single;
        }
        else
                return single;
}
 
singleton* singleton::getInstance(){
        if (!flag)
        {
                single= new singleton;
                flag=true;
                return single;
        }
        else
        {
                return single;
        }
}
 
void singleton::terminate(){
 
        delete single;
        single= NULL;
        perror("Recover allocated mem ");
}
 
 
singleton::singleton(int wIn,int lIn){
 
        width= wIn;
        len= lIn;
}
 
singleton::singleton(){
        width= 8;
        len= 8;
}
//main=======================================
#include <iostream>

 
bool singleton::flag= false;
singleton* singleton::single= NULL;
 
int main(){
 
        singleton* a= singleton::getInstance();
        singleton* b= singleton::getInstance(9,12);
        cout << a->getArea()<<endl;
        //a->terminate();
        cout << b->getArea()<<endl;
        a->terminate();
        b->terminate();
        return 0;
}

