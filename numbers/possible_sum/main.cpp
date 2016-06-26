/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on January 19, 2014, 8:47 PM
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

/* check the number of sums less than number */
void f( std::vector<int> v, int number) {
    //std::copy( v.begin(), v.end(), std::ostream_iterator<int>(std::cout,","));
    //std::cout << std::endl;
    std::vector<int>::iterator it = v.begin();
    
    while ( it != (v.end() - 1)  && it != v.end()) {
        std::vector<int> res;
        std::copy( v.begin(), it, std::back_inserter(res));
        int a = *it++;
        int b = *it++;
        int sum = a + b;
        
        if ( sum < number) {
            res.push_back( sum);
            std::copy( it, v.end(), std::back_inserter(res));
            std::copy( res.begin(), res.end(), std::ostream_iterator<int>(std::cout,","));
            std::cout << std::endl;
            f( res, number);
        }
    }
}

int g( int number) {
    std::map<int, std::vector<int> > map;
    std::vector<int> ones(number, 1);
    f( ones, number);
    return map.size();
}


std::vector<int> f1() {
    std::vector<int> v(1, 1);
    return v;
}

std::vector<int> f2() {
    std::vector<int> v(2, 1);
    return v;
}

int main(int argc, char** argv) {

    g(5);
    return 0;
}

