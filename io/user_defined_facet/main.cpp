/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 20, 2014, 03:57 AM
 */

#include <iostream>
#include <locale>

/*
 * 
 */

enum Season { spring, summer, fall, winter};

class Season_io : public std::locale::facet {
    public:
        Season_io( int i = 0) : std::locale::facet( i) {}
        
        /* make possible to destroy Season_io object */
        ~Season_io() {}
        
        /* string representation of x */
        virtual const std::string& to_str( Season x) const = 0;
        
        /* place Season corresponding to s in x */
        virtual bool from_str( const std::string& s, Season& x) const = 0;
        
        /* facet identifier object. For facet to be
         * found in a locale by has_facet<>() and use_facet<>() */
        static std::locale::id id;
};

std::locale::id Season_io::id;  // definition

/*
 * Note that this << operator is implemented by invoking << for other types. This way, we benefit
 * from the simplicity of using << compared to accessing the ostream’s stream buffers directly, from
 * the locale sensitivity of those << operators, and from the error handling provided for those <<
 * operators. Standard facets tend to operate directly on stream buffers (§D.4.2.2, §D.4.2.3) for 
 * maximum efficiency and flexibility, but for many simple user-defined types, there is no need to drop to
 * the streambuff level of abstraction.
 * 
 * The error handling is simple and follows the error-handling style for built-in types.
 * That is, if the input string didn’t represent a Season in the chosen locale, the 
 * stream is put into the fail state. If exceptions are enabled, this implies that
 * an ios_base::failure exception is thrown.
 */

std::ostream& operator<<( std::ostream s, Season x) {
    const std::locale& loc = s.getloc(); // extract the stream's locale
    
    /* does stream locale loc contain Season_io facet? */
    if( std::has_facet<Season_io>( loc))
        /* perfect. Write to stream using Season_io I/O */
        return s << std::use_facet<Season_io>( loc).to_str( x);
    /* write numeric representation */
    return s << int( x);
}

std::istream& operator>>( std::istream s, Season x) {
    const std::locale& loc = s.getloc(); // extract the stream's locale
    
    /* does stream locale loc contain Season_io facet? */
    if( std::has_facet<Season_io>( loc)) {
        /* perfect. Read alphabetic representation from stream using Season_io I/O */
        const Season_io& f = std::use_facet<Season_io>( loc);
        std::string buf;
        if ( !( s >> buf && f.from_str( buf, x))) s.setstate( std::ios_base::failbit);
        return s;
    }
    /* read numeric representation */
    int i;
    s >> i;
    x = Season( i);
    return s;
}

int main(int argc, char** argv) {
    
    std::locale loc0;                 // copy of the current global locale
    std::locale loc1 = std::locale(); // copy of the current global locale
    std::locale loc2("");            // copy of ‘‘the user’s preferred locale’’
    std::locale loc3( "C");                     // copy of the "C" locale
    std::locale loc4 = std::locale::classic();  // copy of the "C" locale
    std::locale loc5( "POSIX"); // copy of the implementation-defined "POSIX" locale
    
    char c = std::use_facet< std::numpunct<char> > ( std::locale()).decimal_point();
    std::cout << "std::use_facet< std::numpunct<char> > ( std::locale()).decimal_point():" << c << std::endl;

    return 0;
}