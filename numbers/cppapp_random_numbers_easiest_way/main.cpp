/* 
 * File:   main.cpp
 * Author: cf16.eu
 *
 * Created on January 9, 2014, 6:39 PM
 */

#include <iostream>
#include <algorithm>
#include <boost/random.hpp>

/*
 * 
 */
int main(int argc, char** argv) {
    boost::mt19937 rand_generator(std::time(NULL));
    boost::random::uniform_int_distribution<> int_distribution(0, 100);

    //Need to pass generator
    std::cout << int_distribution(rand_generator) << std::endl;

    //Associate generator with distribution
    boost::random::variate_generator<boost::mt19937&,
            boost::random::uniform_int_distribution<>
            > int_variate_generator(rand_generator, int_distribution);

    //No longer need to pass generator
    std::cout << int_variate_generator() << std::endl;
    std::generate_n( std::ostream_iterator<int>(std::cout, ","), 3, int_variate_generator);
    return 0;
}

