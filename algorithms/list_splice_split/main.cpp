/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on May 22, 2014, 2:43 AM
 * 
 * http://stackoverflow.com/q/23794679/1141471
 */

#include <iostream>
#include <list>
#include <vector>

std::vector< std::list<int> > & split( std::list<int>  v,
                   int delim, std::vector< std::list<int> >& elems) {

    std::list<int>::iterator it = v.begin();

    while ( it != v.end()) {
    	std::list<int> l;

        while ( it != v.end() && *it < delim) {
            ++it;
        }
        
        if( it != v.end()) {
        	l.splice( l.begin(), v, v.begin(), ++it);
            it = v.begin();
        } else {
        	l.splice( l.begin(), v, v.begin(), it);
        }
        
        elems.push_back( l);
    }
    return elems;
}


std::vector< std::list<int> > split( const std::list<int>  &v, int delim) {
    std::vector< std::list<int> > elems;
    split( v, delim, elems);
    return elems;
}

int main() {

    int tab[ 13] = { 1, 2, 3, 503, 5, 6, 502, 7, 510, 3, 500, 6, 7};
    std::list<int> v( tab, tab + 13);
    std::vector< std::list<int> > vl;
    vl = split( v, 500);

    int i = 0;
    while( i < vl.size()) {
        std::list<int>::const_iterator it = vl[ i].begin();
	while( it !=  vl[ i].end())
            std::cout << *it++;
	std::cout << std::endl;
        ++i;
    }
	
	return 0;
}

