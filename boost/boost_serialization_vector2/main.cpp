/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on December 19, 2013, 2:23 PM
 */

/*
 * 
 */

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include <iostream>
#include <memory>
#include <fstream>

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class base {
  public:
    int data1;

    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive & ar, const unsigned int file_version) {
        ar & data1;
    }

  public:
    base() {};
    base(int _d) : data1(_d) {}
    virtual void foo() const {std::cout << "base" << std::endl;}
    virtual void data() const {std::cout << "data: " << data1 << std::endl;}
};

class derived : public base {
  public:
    int data2;

    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive & ar, const unsigned int file_version) {
        ar & boost::serialization::base_object<base>(*this);
        ar & data2;
    }

  public:
    derived() {};
    derived(int _b, int _d) : base(_b), data2(_d) {}
    virtual void foo() const {std::cout << "derived" << std::endl;}
    virtual void data() const {std::cout << "data: " << data1 << ", " << data2 << std::endl;}
};

class MySerialization {
public:
    // Serialize the std::vector member of Info  
    template<class Archive>  
    void serialize(Archive & ar, const unsigned int version)  
    {  
      ar & base_vec;   
    }  
     
    std::vector<base*> base_vec;
};

BOOST_CLASS_EXPORT(derived);

void f( base* p) {
    p->foo();
}

void g( base* p) {
    p->data();
}

//template <typename Archive, typename base>
//struct g : public std::binary_function<Archive&, base*, void> {
//    void operator() (Archive& ar, base* b) const { ar.operator&(*b);}
//};
//
//template <typename Archive, typename base>
//struct h : public std::binary_function<Archive&, base, void> {
//    void operator() (Archive& ar, base& b) const { ar.operator&(b);}
//};
//
//template<typename Archive>
//void serialize(Archive& ar, std::vector<base*>& objs, const unsigned version) {
//    std::for_each( objs.begin(), objs.end(), bind1st(g<Archive,base>(),ar));
//  //ar & objs;
//}
//
//template<typename Archive>
//void serialize(Archive& ar, std::vector<base>& objs, const unsigned version) {
//    std::for_each( objs.begin(), objs.end(), bind1st(h<Archive,base>(),ar));
//  //ar & objs;
//}

int main(int argc, char *argv[]) {

    // client
    // Assign to base type
//    base* b1 = new derived(1, 2);

//    std::ostringstream oss;
//    boost::archive::text_oarchive oa(oss);
//    oa & b1;

//    // server
//    // Retrieve derived type from base
//    base* b2;

//    std::istringstream iss(oss.str());
//    boost::archive::text_iarchive ia(iss);
//    {
//        base *temp;
//        ia & temp;
//        b2 = temp;
//    }
//    cout << b2->data1 << endl;
//    cout << (dynamic_cast<derived*>(b2))->data2 << endl;
//    b2->foo();
//////////////////////////////////////////////////////////
    //client
    {
    std::ofstream oss2("file_arch.dat");
    boost::archive::text_oarchive oa2(oss2);
    MySerialization ms;
    ms.base_vec.push_back( new base(5));
    ms.base_vec.push_back( new base(6));
    ms.base_vec.push_back( new derived(7,8));
    std::cout<<"s:"<<ms.base_vec.size();
////    v.assign( 2, new base(0));
////    v.assign( 2, new derived( 1, 2));
////    v.assign( 2, new base(0));
//    v.push_back( base( 3));
//    v.push_back( base( 2));
//    v.push_back( base( 1));
    //std::cout<<v.size();
//
    oa2 & ms;
    }
    std::cout<<"-------";
    //server
    MySerialization temp2;
    {
        std::ifstream iss2("file_arch.dat");
        boost::archive::text_iarchive ia2(iss2);
        std::cout<<"t:"<<temp2.base_vec.size();
        ia2 & temp2;
        std::cout<<temp2.base_vec.size();
    }
    std::cout<<temp2.base_vec.size();
////    v2 = temp2;
    std::for_each( temp2.base_vec.begin(), temp2.base_vec.end(), g);
////    std::cout<<temp2.size();

    return 0;
}



