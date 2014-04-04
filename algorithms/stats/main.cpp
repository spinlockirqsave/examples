#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
using namespace boost::accumulators;


int main() {
    // Define an accumulator set for calculating the mean, max, and min
    accumulator_set<double, features<tag::min, tag::max, tag::mean> > acc;

    int num = -1;
    bool empty = true;

    while ( std::cin >> num && num >= 0) {
        empty = false;
        acc( num);
    }

    if ( ! empty) {
        // Display the results ...
        std::cout << "Mean: " << mean( acc) << std::endl;
        std::cout << "Min: " << min( acc) << std::endl;
        std::cout << "Max: " << max( acc) << std::endl;  
    }

    return 0;
}