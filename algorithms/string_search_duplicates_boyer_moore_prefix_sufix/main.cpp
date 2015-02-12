/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 17, 2014, 6:37 PM
 */

#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

#include <fstream>

class SkipTable
{
    public:
    typedef std::size_t size_type;

    private:
    unsigned tableSize;

    public:
    SkipTable()
    {
        tableSize = unsigned( std::numeric_limits<unsigned char>::max()) + 1;
        size_type size;
        std::pair< size_type*, size_type> p = std::get_temporary_buffer<size_type>(tableSize);
        m_table = p.first;
        if( tableSize <= size) std::fill_n( m_table, tableSize, 1);
        else {
            std::return_temporary_buffer<size_type>(m_table);
            m_table = 0;
        }
    }

    private:
    SkipTable(const SkipTable&); // No copy
    SkipTable& operator = (const SkipTable&); // No copy

    public:
    ~SkipTable() {
        std::return_temporary_buffer<size_type>(m_table);
    }

    void set(const char* s, size_type len) {
        if(len < 1) len = 1;
        if(m_table) {
            m_len = len;
            std::fill_n(m_table, tableSize, m_len);
            while(len)
                m_table[unsigned(*s++)] = len--;
        }
    }

    const size_type get(size_type pos) const {
        size_type n = (m_table && pos < tableSize) ? m_table[pos] : 1;
        return n;
    }

    operator bool() const { return m_table; }

    private:
    size_type* m_table;
    size_type m_len;
};


const char* find(
    SkipTable& skip,
    const char* str, const std::size_t strlen,
    const char* substr, const std::size_t substrlen)
{
    typedef std::char_traits<char> traits_type;
    typedef std::size_t size_type;

    if (substrlen == 0 || strlen < substrlen) return 0;

    const char* end = str + strlen - substrlen;

    if(skip && 4 < substrlen && substrlen < strlen - substrlen) {

        // Boyer-Moore-Search
        //===================


        skip.set(substr, substrlen);
        while(str <= end) {
            if(traits_type::compare(str, substr, substrlen) == 0)
                break;
            str += skip.get(*(str + substrlen));
        }
        return (str <= end) ? str : 0;
    }
    else {
        // Brute Search
        //=============

        while(str <= end) {
            if (traits_type::compare(str, substr, substrlen) == 0)
                return str;
            ++str;
        }
    }
    return 0;
}


#include <map>

void find_duplicates(const char* s, const std::size_t size) {
    std::map<std::string, unsigned> duplicates;
    SkipTable skip;
    for(std::size_t n = 1; n < size / 2; ++n) {
        for(std::size_t i = 0; i <= size - 2*n; ++i) {
            const char* p = find(skip, s + i + n, size - i - n, s + i, n);
            if(p) {
                ++duplicates[std::string(p, n)];
            }
        }
    }
    // Increment the counts
    for( std::map<std::string, unsigned>::iterator d = duplicates.begin(); d != duplicates.end(); ++d) {
        ++((*d).second);
        std::cout << '[' << ((*d).second) << "] \"" << ((*d).first) << "\"\n";
    }
}

int main() {
    std::ifstream ifs( "/home/peter/Downloads/Sheetal09Singular.pdf");
    std::string in( ( std::istreambuf_iterator<char>( ifs)),
                      std::istreambuf_iterator<char>());
    std::string text = "Some text for matching sub-strings in the text.";
    find_duplicates( in.c_str(), in.size());
}

