/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 24, 2014, 10:13 AM
 */

#include <vector>
#include <iostream>
#include <stdexcept>

/**
 * 
 * @param graph                 dag as a vector of vectors
 * @param i                     current index in graph
 * @param color                 vector of colors
 * @param sortedTopologically   result sorted topologically
 */
void depth_first_search( std::vector<std::vector<int> > const& graph,
       int i, std::vector<int>& color, std::vector<int>& sortedTopologically) {

    enum Color { WHITE, GRAY, BLACK};
    color[ i] = GRAY;

    const std::vector<int>& edges = graph[ i];
    for ( std::vector<int>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
        
        /* cyclic dependency check */
        if( color[ *it] == GRAY)
            throw std::runtime_error( "cyclic dependency");
        
        if( color[ *it] == WHITE) {
            depth_first_search( graph, *it, color, sortedTopologically);
        }
    }
    
    color[ i] = BLACK;
    sortedTopologically.push_back( i);
}

/**
 * complexity O( V + E)
 * since it take O( V + E) to perform depth first search
 * and O( 1) time to insert each of the |V| vertices onto
 * the result, O( V) to construct colors
 * @param graph                 dag as a vector of vectors
 * @param sortedTopologically   result sorted topologically
 */
void depth_first_search( std::vector<std::vector<int> > const& graph,
                                        std::vector<int>& sortedTopologically) {
    enum Color { WHITE, GRAY, BLACK};
    int size = graph.size();
    std::vector<int> color( size, WHITE);
    
    for( int i = 0; i < size; ++i) {
        
        if( color[ i] == WHITE)
            depth_first_search( graph, i, color, sortedTopologically);
    }  
}

/**
 * This function provides a topological sort of the directed
 * acyclic graph provided as its input
 * @param orders        dag as a vector of vectors
 * @param sortedOrders  result sorted topologically
 */
void taskOrder( std::vector<std::vector<int> > const& orders, std::vector<int>& sortedOrders) {
    depth_first_search( orders, sortedOrders);
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
    taskOrder( tasks, res);

    for ( std::vector<int>::const_iterator it = res.begin();
            it != res.end(); ++it) {
        std::cout << ( *it);
    }
    
    return 0;
}