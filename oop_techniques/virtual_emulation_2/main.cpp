#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>

#include "classes.h"

class Object;


namespace {

    void ab( Object &obj1, Object &obj2);

    typedef void ( *hit_f_ptr)( Object& obj1, Object& obj2);
    typedef std::map< std::pair< std::string, std::string>, hit_f_ptr> HitMap;

    HitMap *init_hit_map()
    {
        HitMap *phm = new HitMap;
        ( *phm)[ std::make_pair( "A", "B")] = &ab;
        
        return phm;
    }

    hit_f_ptr lookup( const std::string& s1, const std::string &s2)
    {
        static std::auto_ptr<HitMap> aphm( init_hit_map()); 
        HitMap::const_iterator it = aphm->find( std::make_pair( s1, s2));
        if( it == aphm->end())
            return 0;
        return ( *it).second;
    }

    void collide( Object& obj1, Object &obj2)
    {
        hit_f_ptr phf = lookup( typeid(obj1).name(), typeid(obj2).name());
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
        std::cout << "ab:" << typeid(obj1).name() << "," << typeid( obj2).name();
    }
}

int main()
{
    A a;
    B b;
    collide( a, b);
}