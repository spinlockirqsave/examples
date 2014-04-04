/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on May 9, 2013, 9:48 PM
 */

#include <cstdlib>

// For ints
// replace _real_ with _int_, 
// <double> with <int> and use integer constants

#include <random>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <random>

int main()
{
    std::default_random_engine rng(std::random_device{}()); 
    std::normal_distribution<float> dist(0.0f, 1.0f);  //(min, max)

    //get one
    const float random_num = dist(rng);

    std::vector<float> v(10);
//
//    std::generate_n( 
//        v.begin(), 
//        10, 
//        [&]{ return dist(rng);} ); 
//    std::copy(v.begin(), v.end(), std::ostream_iterator<float> (std::cout," "));
    return 0;
}

