/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 27, 2014, 12:34 PM
 */

#include <iostream>
#include <locale>
#include <string>
#include <fstream>

class codecvt_to_upper : public std::codecvt<wchar_t, char, std::mbstate_t> {
public:

    explicit codecvt_to_upper(size_t r = 0) : std::codecvt<wchar_t, char, std::mbstate_t>(r) {
        int i = 9;
    }
protected:
    result do_in(state_type& state, const extern_type* from, const extern_type* from_end,
            const extern_type*& from_next, intern_type* to, intern_type* to_end,
            intern_type*& to_next) const;

    result
    do_out(state_type& __state, const intern_type* __from,
            const intern_type* __from_end, const intern_type*& __from_next,
            extern_type* __to, extern_type* __to_end,
            extern_type*& __to_next) const {
        return codecvt_to_upper::ok;
    }

    result
    do_unshift(state_type& __state, extern_type* __to,
            extern_type* __to_end, extern_type*& __to_next) const {
        return codecvt_to_upper::ok;
    }

    int
    do_encoding() const throw () {
        return 1;
    }

    bool
    do_always_noconv() const throw () {
        return false;
    }

    int
    do_length(state_type&, const extern_type* __from,
            const extern_type* __end, size_t __max) const {
        return 1;
    }

    int
    do_max_length() const throw () {
        return 10;
    }
};

codecvt_to_upper::result codecvt_to_upper::do_in(state_type& state, const extern_type* from,
        const extern_type* from_end, const extern_type*& from_next, intern_type* to,
        intern_type* to_end, intern_type*& to_next) const {
    codecvt_to_upper::result res = codecvt_to_upper::error;
    const std::ctype<char>& ct = std::use_facet<std::ctype<char> >( std::locale());

    const extern_type* p = from;
    while( p != from_end && to != to_end) {
        *to++ = ct.toupper( *p++);
    }
    from_next = p;
    to_next = to;
    res = codecvt_to_upper::ok;
    return res;
}
/*
 * 
 */
int main(int argc, char** argv) {

    std::locale ulocale( std::locale(), new codecvt_to_upper);
 
    std::wstring piter = L"piter";
    std::wofstream ws( "out.txt");
    ws << piter;
    ws.close();
    
    std::wifstream in( "out.txt");
    in.imbue( ulocale);
 
    wchar_t c;
 
    while (in >> c)
    {
        std::wcout << c;
    }
    return 0;
}

