#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>

#include "classes.h"

class Object;


namespace {

    void ab( Object &obj1, Object &obj2);
    void ba( Object &obj1, Object &obj2);
    void oo( Object &obj1, Object &obj2);

    typedef void ( *hit_f_ptr)( Object& obj1, Object& obj2);
    typedef std::map< std::pair< const std::type_info*, const std::type_info*>, hit_f_ptr> HitMap;

    HitMap *init_hit_map()
    {
        HitMap *phm = new HitMap;
        ( *phm)[ std::make_pair( &typeid(A), &typeid(B))] = &ab;
        ( *phm)[ std::make_pair( &typeid(B), &typeid(A))] = &ba;
        ( *phm)[ std::make_pair( &typeid(Object), &typeid(Object))] = &oo;
        
        return phm;
    }

    hit_f_ptr lookup( const std::type_info* s1, const std::type_info* s2)
    {
        static std::auto_ptr<HitMap> aphm( init_hit_map()); 
        HitMap::const_iterator it = aphm->find( std::make_pair( s1, s2));
        if( it == aphm->end())
            return 0;
        return ( *it).second;
    }

    void collide( Object& obj1, Object &obj2)
    {
        hit_f_ptr phf = lookup( &typeid(obj1), &typeid(obj2));
        if( phf == 0) {
            std::cout << "oh, dear";
            return;
        }

        phf( obj1, obj2);
    }
}

namespace {
    void ab( Object &obj1, Object &obj2)
    {
        std::cout << "ab:" << typeid(obj1).name() << "," << typeid( obj2).name() << std::endl;
    }

    void ba( Object &obj1, Object &obj2)
    {
        std::cout << "ba:" << typeid(obj1).name() << "," << typeid( obj2).name() << std::endl;
    }

    void oo( Object &obj1, Object &obj2)
    {
        std::cout << "oo:" << typeid(obj1).name() << "," << typeid( obj2).name() << std::endl;
    }
}

int main()
{
    A a;
    B b;
    Object &o1 = a;
    Object &o2 = b;
    collide( o1, o2);
    collide( o2, o1);
    collide( o1, o1);
}