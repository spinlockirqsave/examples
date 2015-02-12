/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 22, 2014, 4:30 PM
 */

#include <iostream>                  // for std::cout

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>

using namespace boost;

/*
 * 
 */
int main(int, char*[]) {

    typedef property < edge_weight_t, double >Weight;
    typedef adjacency_list < vecS, vecS, undirectedS,
            no_property, Weight > UndirectedGraph;

    const int V = 3;
    UndirectedGraph undigraph( V);
    graph_traits < UndirectedGraph >::vertex_descriptor zero, one, two;
    graph_traits < UndirectedGraph >::out_edge_iterator out, out_end;
    graph_traits < UndirectedGraph >::in_edge_iterator in, in_end;

    zero = vertex(0, undigraph);
    one = vertex(1, undigraph);
    two = vertex(2, undigraph);
    add_edge(zero, one, undigraph);
    add_edge(zero, two, undigraph);
    add_edge(one, two, undigraph);

    std::cout << "out_edges(0): ";
    for (boost::tie(out, out_end) = out_edges(zero, undigraph); out != out_end; ++out)
        std::cout << *out;
    std::cout << std::endl << "in_edges(0): ";
    for (boost::tie(in, in_end) = in_edges(zero, undigraph); in != in_end; ++in)
        std::cout << *in;
    std::cout << std::endl;
    return 0;
}



