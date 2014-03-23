/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 20, 2014, 03:57 AM
 */

#include <iostream>
#include <locale>
#include <algorithm>
#include <sstream>

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

std::ostream& operator<<( std::ostream& s, Season x) {
    const std::locale& loc = s.getloc(); // extract the stream's locale
    
    /* does stream locale loc contain Season_io facet? */
    if( std::has_facet<Season_io>( loc))
        /* perfect. Write to stream using Season_io I/O */
        return s << std::use_facet<Season_io>( loc).to_str( x);
    /* write numeric representation */
    return s << int( x);
}

std::istream& operator>>( std::istream& s, Season& x) {
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
    s.ignore( 1);
    x = Season( i);
    return s;
}

class US_season_io : public Season_io {
    static const std::string seasons[];
public:
    const std::string& to_str( Season) const;
    bool from_str( const std::string&, Season&) const;
    // note: no US_season_io::id
};

const std::string US_season_io::seasons[] = { "spring", "summer", "fall", "winter"};

const std::string& US_season_io::to_str( Season x) const {
    if( ( x < spring) || ( winter < x)) {
        static const std::string ss = "no-such-season";
        return ss;
    }
    return seasons[ x];
}

bool US_season_io::from_str( const std::string& s, Season& x) const {
    const std::string* beg = &seasons[spring];
    const std::string* end = &seasons[winter] + 1;
    const std::string* p = std::find( beg, end, s);
    if( p == end) {
        std::istringstream iss( s);
        int i;
        iss >> i;
        x = Season( i);
        return false;
    }
    x = Season( p - beg);
    return true;
}


int main(int argc, char** argv) {

    Season y;
    /* use default locale (no Season_io facet) implies integer I/O*/
    std::cin >> y;
    std::cout << y << std::endl;
    
    std::locale loc( std::locale(), new US_season_io);
    std::cout.imbue( loc); // use locale with Season_io facet
    std::cin.imbue( loc);
    
    std::cin >> y;
    std::cout << y << std::endl;
    return 0;
}