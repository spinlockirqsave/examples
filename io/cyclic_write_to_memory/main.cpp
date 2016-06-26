/* 
 * File:   main.cpp
 * Author: peter 
 * http://stackoverflow.com/questions/21597562/adapting-c-std-boost-iostreams-to-provide-cyclic-write-to-memory-block
 *
 * Created on February 7, 2014, 3:35 PM
 */

#include <iostream>
#include <cstdio>
using namespace std;

/*
 * 
 */
class rollingstreambuf : public std::basic_streambuf< char>
{
public:
    typedef std::basic_streambuf< char> Base;

    rollingstreambuf(Base::char_type* baseptr, size_t size)
    {
        setp(baseptr, baseptr + size);
    }

protected:
    virtual int_type overflow (int_type c)
    {
        // reset position to start of buffer
        setp(pbase(), epptr());
        return putchar(c);
    }

    virtual std::streamsize xsputn (const char* s, std::streamsize n)
    {
        if (n >= epptr() - pptr())
            // reset position to start of buffer
            setp(pbase(), epptr());
        return Base::xsputn(s, n);
    }
};

int main(int argc, char** argv) {

    char buffer[100];
    rollingstreambuf buf(buffer, sizeof (buffer));
    std::basic_ostream< char> out(&buf);

    for (int i = 0; i < 6; i++) {
        out << "Mumblemumble " << i << '\n';
    }
    out << std::ends; //write terminating NULL char
    std::cout << buffer;
    /*
     prints
       Mumblemumble 0
       Mumblemumble 1
       Mumblemumble 2
       Mumblemumble 3
       Mumblemumble 4
       Mumblemumble 5
     */

    for (int i = 0; i < 20; i++) {
        out << "Mumblemumble " << i << '\n';
    }
    out << std::ends; //write terminating NULL char
    std::cout << buffer;
        /*
     prints
       Mumblemumble 18
       Mumblemumble 19
     */
    
    return 0;
}

