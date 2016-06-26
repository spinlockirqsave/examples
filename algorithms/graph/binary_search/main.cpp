/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on April 22, 2014, 10:31 PM
 */

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdexcept>

int binarySearch( std::vector<int> const& v, int const& val)
{
	int left = 0, right = v.size() - 1, range, result = -1;
	if( left <= right)
	{
		while( true)
		{
			range = right - left;
			if( v[ left] > v[ right])
			{
				throw std::runtime_error( "the vector is not sorted");
			}
			if( range == 0)
			{
				if(v[ left] == val) result = left;
				else result = -1;
				break;
			}
			else if ( range == 1)
			{
				if(v[left]==val) result = left;
				else if( v[ right] == val) result = right;
				else result = -1;
				break;
			}
			else
			{
				result = range / 2 + left;
				if ( v[ result] == val) break;
				else if ( v[ result] < val) left = result;
				else right = result;
			}
		}
	}
	while( (result>0) && ( v[ result-1] == v[ result])) --result;
	return result;
}

/*
 * 
 */
int main( int argc, char** argv) {

    return 0;
}

