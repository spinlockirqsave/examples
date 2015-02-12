/* 
 * File:   main.cpp
 * Author: piotruś peter cf16.eu
 *
 * Created on November 16, 2013, 11:00 PM
 */

    #include <fstream>
    #include <vector>
    #include <string>
    #include <sstream>
    #include <iterator>
    #include <algorithm>
    #include <iostream>
    
    int main()
    {
       std::string line;
       std::ifstream ifs("doubles.txt");
       std::vector< std::vector<double> > all_integers;

       while ( std::getline( ifs, line ) ) {
          std::istringstream is( line );
//          all_integers.push_back( 
//            std::vector<int>( std::istream_iterator<int>(is),
//                              std::istream_iterator<int>() ) );
          std::vector<double> numbers = std::vector<double>
                                  ( std::istream_iterator<double>(is),
                                    std::istream_iterator<double>());
          std::copy( numbers.begin(), numbers.end(), std::ostream_iterator<double>( std::cout, " "));
       }
    }

