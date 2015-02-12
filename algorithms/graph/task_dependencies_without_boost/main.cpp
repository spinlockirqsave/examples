/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 22, 2014, 10:29 PM
 */

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdexcept>

void resolve( std::vector<std::vector<int> > const& orders,
        int i, std::vector<bool>& visited, std::vector<bool>& tmpVisited,
        std::vector<int>& stack)
{
	tmpVisited[ i] = true;
	const std::vector<int>& edges = orders[ i];
	for( std::vector<int>::const_iterator it = edges.begin(); it != edges.end(); ++it)
	{
		if( tmpVisited[*it])
		{
			// circular dependecies
			std::cout<< "circular dependecy found in "<<(*it)<<"\n";
			throw std::runtime_error( "circular dependecy found");
		}
		else if( !visited[ *it])
		{
			resolve( orders, *it, visited, tmpVisited, stack);
		}
	}
	tmpVisited[ i] = false;
	visited[ i] = true;
	stack.push_back( i);
}

std::vector<int> resolve_orders_dependencies( std::vector<std::vector<int> > const& orders)
{
	std::vector<int> stack;
	int size = orders.size();
	std::vector<bool> visited( size, false);
	std::vector<bool> tempVisited( size, false);
        
	for( int i = 0; i < size; ++i)
	{
		if( !visited[ i])
                    resolve( orders, i, visited, tempVisited, stack);
	}
	return stack;
}

/*
 * 
 */
int main(int argc, char** argv) {

    std::vector<std::vector<int> > tasks;
    tasks.push_back( std::vector<int>());
    std::vector<int> v;
    v.push_back( 0);
    v.push_back( 2);
    tasks.push_back( v);
    tasks.push_back( std::vector<int>());
    
    std::vector<int> res;
    res = resolve_orders_dependencies( tasks);

    for ( std::vector<int>::const_iterator it = res.begin();
            it != res.end(); ++it) {
        std::cout << (*it);
    }
    return 0;
}

