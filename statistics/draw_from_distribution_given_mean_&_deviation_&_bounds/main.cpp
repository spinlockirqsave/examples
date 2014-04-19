/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 18, 2014, 9:09 PM
 */

#include <boost/random.hpp>
#include <boost/random/bernoulli_distribution.hpp>

double generate_from_bernoulli_distribution(double mi, double d, double a, double b) {
    if (b <= a || d < 0) throw std::out_of_range( "invalid parameters");
    if (d > std::min(mi - a, b - mi)) throw std::out_of_range( " invalid standard deviation");
    
    double x1 = mi - d;
    double x2 = mi + d;

    boost::mt19937 rng; // I don't seed it on purpouse (it's not relevant)
    boost::bernoulli_distribution<> bd;
    boost::variate_generator<boost::mt19937&,
            boost::bernoulli_distribution<> > var_ber( rng, bd);

    double bernoulli = var_ber();
    return ( x1 + bernoulli * 2 * d); // return x1 on 0, or x2 on 1
}

void generate_n_from_bernoulli_distribution( double mi, double d, double a, double b,
                                                        std::vector<double>& res, int n) {
    if (b <= a || d < 0) throw std::out_of_range( "invalid parameters");
    if (d > std::min(mi - a, b - mi)) throw std::out_of_range( " invalid standard deviation");
    
    double x1 = mi - d;
    double x2 = mi + d;

    boost::mt19937 rng; // I don't seed it on purpouse (it's not relevant)
    boost::bernoulli_distribution<> bd;
    boost::variate_generator<boost::mt19937&,
            boost::bernoulli_distribution<> > var_ber( rng, bd);

    int i = 0;
    for (; i < n; ++i) {
        double bernoulli = var_ber();
        res.push_back( x1 + bernoulli * 2 * d); // push_back x1 on 0, or x2 on 1
    }
}

/*
 * 
 */
int main()
{
  double rc = generate_from_bernoulli_distribution( 4, 1, 0, 10);
  std::vector<double> sample;
  generate_n_from_bernoulli_distribution( 4, 1, 0, 10, sample, 100);
  return 0;
}

