/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on March 22, 2013, 8:14 PM
 */

#include <cstdlib>
#include <iostream>
#include <locale>
#include <string>
using namespace std;

struct my_facet : public std::numpunct<char>{
        explicit my_facet(size_t refs = 0) : std::numpunct<char>(refs) {}
        virtual char do_thousands_sep() const { return ','; }
        virtual std::string do_grouping() const { return "\003"; }
};
//struct my_facet{
//
//};

class bucket_string {
        public:
            //bucket_string(bucket_string b);
            bucket_string(){}
            bucket_string(bucket_string & rhs);
            bucket_string & operator=(bucket_string & rhs);
            virtual ~bucket_string(){}
 };
 
 string getString(){

  //cout << "Please enter a string to process ";
  //cin >> string;
  //cout << "String in getString before process: " << string << "\n";
  string string;
  getline(cin,string, 'r');
  cout << "String after processing: " << string << "\n"; // here string is not printed
  return string;
 }
/*
 * 
 */
 class GlobalClass
{
    int m_value;
    static GlobalClass *s_instance;
    GlobalClass(int v = 0)
    {
        m_value = v;
    }
  public:
    int get_value()
    {
        return m_value;
    }
    void set_value(int v)
    {
        m_value = v;
    }
    static GlobalClass *instance()
    {
        if (!s_instance)
          s_instance = new GlobalClass;
        return s_instance;
    }
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object itself.
GlobalClass *GlobalClass::s_instance = 0;

void foo(void)
{
  GlobalClass::instance()->set_value(1);
  cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar(void)
{
  GlobalClass::instance()->set_value(2);
  cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}


int main(int argc, char** argv) {
    std::cout << "main: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
    foo();
    bar();
  
    getString();
    bucket_string a;
    bucket_string b;
    cout<<"before. number 5000000: "<<5000000<<endl;
    
    std::locale global;
    std::locale withgroupings(global, new my_facet);
    std::locale was = std::cout.imbue(withgroupings);
    
    cout<<"after. number 5000000: "<<5000000<<endl;
    
    std::cout.imbue(was);
    
    cout<<"and again as before. number 5000000: "<<5000000<<endl;

    return 0;
}

