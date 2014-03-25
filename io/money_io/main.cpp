/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 25, 2014, 5:01 PM
 */

#include <iostream>
#include <locale>

class Money {
public: 
    Money( long int amount) : amount_(amount) {}
    operator long int() { return amount_; }
private:
    long int amount_;
};

class My_money_io : public std::moneypunct<char, true > {
public:

    explicit My_money_io(size_t r = 0) : std::moneypunct<char, true > (r) {
    }

    string_type do_curr_symbol() const {
        return "USD";
    }
    
    string_type do_positive_sign() const {
        return "+";
    }
    
    typedef std::money_base mb;

    std::money_base::pattern do_pos_format() const {
        mb::pattern pattern;
        pattern.field[ 0] = mb::sign;
        pattern.field[ 1] = mb::symbol;
        pattern.field[ 2] = mb::none;
        pattern.field[ 3] = mb::value;
        return pattern;
    }
};

std::ostream& operator<< ( std::ostream& s, Money& m) {
    
    return s;
}
/*
 * 
 */
int main(int argc, char** argv) {

    double d = 123;
    std::ostream& s = std::cout;
    std::ostream::sentry guard( s);
    
    try {
        const std::money_put<char>& f = std::use_facet< std::money_put<char> >( s.getloc());
        std::cout << std::use_facet< std::moneypunct<char, true> >( s.getloc()).curr_symbol();
        std::cout << std::use_facet< std::moneypunct<char, true> >( s.getloc()).decimal_point();
        std::cout << std::use_facet< std::moneypunct<char, true> >( s.getloc()).negative_sign();
        std::money_base::pattern pattern = std::use_facet< std::moneypunct<char> >( s.getloc()).pos_format();
        
        if ( f.put( s, true, s, s.fill(), d).failed()) { 
            s.setstate( std::ios_base::badbit);
        }
    } catch ( std::exception& e) {
        std::cout << e.what();
    }
    
    try {
        s.imbue( std::locale( s.getloc(), new My_money_io));
        const std::money_put<char>& f = std::use_facet< std::money_put<char> >( s.getloc());
        std::cout << std::use_facet< My_money_io >( s.getloc()).curr_symbol();

        if ( f.put( s, true, s, s.fill(), d).failed()) { 
            s.setstate( std::ios_base::badbit);
        }
    } catch ( std::exception& e) {
        std::cout << e.what();
    }
    
    return 0;
}

