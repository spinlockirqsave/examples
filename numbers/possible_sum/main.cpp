/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on January 19, 2014, 8:47 PM
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

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
/*
 * 
 */

std::vector<int> f1() {
    std::vector<int> v(1, 1);
    return v;
}

std::vector<int> f2() {
    std::vector<int> v(2, 1);
    return v;
}

//std::vector<int> h( int number, int current, std::vector<int> vin, int sum) { //10,10,10,0
//    if ( sum == 1) {
//        std::vector<int> res(vin);
//        res.push_back(1); // 9,1
//        std::copy( res.begin(), res.end(), std::ostream_iterator<int>(std::cout,","));
//        std::cout << std::endl;
//    }
//    
//    if ( sum == 2) {
//        std::vector<int> res(vin); // 8
//        res.resize( res.size()+2, 1); // 8,,1,1
//        std::copy( res.begin(), res.end(), std::ostream_iterator<int>(std::cout,","));
//        std::cout << std::endl;
//        
//        res.clear();
//        res(vin);  // 8
//        res.resize( res.size()+1, 2); // 8,2
//        std::copy( res.begin(), res.end(), std::ostream_iterator<int>(std::cout,","));
//        std::cout << std::endl;
//    }
//    
//    std::copy(vin.begin(), vin.end(), std::ostream_iterator<int>(std::cout, ",")); // 10
//    std::cout << std::endl;
//    
//    if (current > 1) { // 10
//        --current;
//        vin.clear();
//        vin.push_back( current); // 9
//        vin.push_back( sum+1);
//        h(10,current,vin,sum+1);
//    }
//    return v;
//}

//std::vector<int> fn(int number, int sumres, std::vector<int> vfn) { //5,0
//    if (sumres == 2) return std::vector<int>(2, 1);
//    if (sumres == 1) return std::vector<int>(1, 1);
//
//    for (int i = number; i; --i) {
//        std::vector<int> vres;
//        vres.push_back(i);
//        if (sumres)
//            fn( i-1, sumres + 1, vres);
//    }
//    return v;
//}

int ff( int x) {
    int& x_ref = x;
    int b = 3;
    x_ref = b;
    x++;
    int* c = &x;
    return *c - x_ref;
}
int main(int argc, char** argv) {

    //g(5);
    int i = ff(1);
    return 0;
}

