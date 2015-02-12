/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 23, 2014, 4:59 PM
 */

#include <iostream>
#include <vector>
#include <stdexcept>


/**
 * Complexity of binary search is O( log( N))
 * as it halves the range of search in each iteration
 * @param v     vector of sorted values
 * @param val   value to be searched
 * @return      the index of val in v or -1 on error
 */
int binarySearch( std::vector<int> const& v, int const& val)
{
    if( v.empty())
        throw std::runtime_error( "the vector is empty");
    
    int left = 0, right = v.size() - 1, range, result = -1;
    
    if( left <= right) {
        
        while( true) {
            
            range = right - left;
            
            /* this is only thrown when we discover that v is not sorted
             * but v can be not sorted and we can still find val by coincidence
             * so don't treat this test as a check for sort in general */
            if( v[ left] > v[ right])
                throw std::runtime_error( "the vector is not sorted");
                        
	    if( range == 0) {
                
                if( v[ left] == val) result = left;
		else result = -1;
		break;
                
	    } else if ( range == 1) {
                
	        if( v[ left] == val) result = left;
                else if( v[ right] == val) result = right;
                else result = -1;
		break;
                
	    } else {
                
	        result = range / 2 + left;
                
                if( v[ left] > v[ result])
                    throw std::runtime_error( "the vector is not sorted");
                
		if ( v[ result] == val) break;
                
		if ( v[ result] < val) left = result;
		else right = result;
	    }
	}
    }
    
    /* move to the left in case of duplicated values 
     * and return left-most occurence */
    while( ( result > 0) && ( v[ result-1] == v[ result])) --result;
    return result;
}

/*
 * 
 */
int main(int argc, char** argv) {

    {
        int array[] = {1, 2, 3, 4, 6, 20, 130, 500, 1000};
        std::vector<int> v( array, array + 9);
        int res = -1;

        try {
            res = binarySearch( v, 3);
        } catch ( std::exception& e) {
            std::cout << e.what();
        }

        std::cout << res << std::endl;
    }
    
    {
        int array[] = {1, 2, 3, 4, 6, 20, 130, 500, 3, 1000};
        std::vector<int> v( array, array + 10);
        int res = -1;

        try {
            res = binarySearch( v, 3);
        } catch ( std::exception& e) {
            std::cout << e.what();
        }

        std::cout << res << std::endl;
    }
    
    {
        int array[] = {1, 2, 3, 4, 6, 20, 130, 500, 7, 1000};
        std::vector<int> v( array, array + 10);
        int res = -1;

        try {
            res = binarySearch( v, 600);
        } catch ( std::exception& e) {
            std::cout << e.what();
        }

        std::cout << res << std::endl;
    }
    

    return 0;
}

