/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on March 1, 2014, 4:41 PM
 * http://stackoverflow.com/questions/22116158/whats-wrong-with-this-stream-buffer/22116751#22116751
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>

class io_buffer : public std::streambuf
{
public:
    io_buffer(std::ostream& os, int buf_size = 4)
        : os_(os), buffer(buf_size)
    {
        os_.clear();
        char* beg = buffer.data();
        setp(beg, beg + buffer.size());
    }

    int_type overflow(int_type c)
    {
        if (os_ && !traits_type::eq_int_type(c, traits_type::eof()))
        {
            *pptr() = traits_type::to_char_type(c);
            pbump(1);

            if (flush())
            {
                buffer.clear();
                pbump(-buffer.size()); // for it avoids multiple calls to overflow()
                setp(buffer.data(), buffer.data() + buffer.size());
                return c;
            } else
                return traits_type::eof();
        }

        return traits_type::not_eof(c);
    }

    bool flush()
    {
        return os_.write(pbase(), pptr() - pbase());
    }

    int sync()
    {
        return flush() ? 0 : -1;
    }
private:
    std::ostream& os_;
    std::vector<char> buffer;
};

int main()
{
    std::ostringstream oss;
    io_buffer buf(oss);

    std::ostream os(&buf);
    std::string str("Hello, World\n but I am not a helicopter");

    os << str;
    std::cout << oss.str() << std::endl;
}

