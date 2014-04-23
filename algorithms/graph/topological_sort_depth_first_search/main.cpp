/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 23, 2014, 2:42 AM
 */

#include <stdio.h>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include <boost/foreach.hpp>

struct Vertex {
    enum Color { WHITE, GRAY, BLACK};
    int color;
    int d; // time of discovery
    int f; // time of finish
    int pi;
    std::vector<int> adjacencyList;
    int idx;
    
    explicit Vertex( int idx) : idx( idx), color( WHITE), d( -1), f( -1), pi( -1) {}
};


/**
 * Graph, directed acyclic ( dag)
 */
struct Graph {
    /* sorted vector of vertices*/
    std::vector<Vertex> V;
    
    /* number of vertices*/
    int const N;
    
    /* Number of edges. Edge ( u, v) indicates that
     * u "is used by" v, so v "depends on" u */
    int E;
    
    std::vector<int> const& adjacency( Vertex const& u) const {
        return V[ u.idx].adjacencyList;
    }
    
    static bool verticesCompare( Vertex const& lhs, Vertex const& rhs) {
        return lhs.idx < rhs.idx;
    }
    
    /**
     * Constructor with invariant: graph contains normalized
     * vector of vertices with normalized indices and adjacency lists
     * @param v vertices
     */
    explicit Graph( std::vector<Vertex>& v) : V( v), N( v.size()) {

        std::sort( V.begin(), V.end(), &verticesCompare);
        int i = V[0].idx;
        
        /* normalize indices to start from 0 */
        if( V[ 0].idx > 0) {
            int norm = V[ 0].idx;
            for( int i = 0; i < N; ++i) {
                V[ i].idx -= norm;
                E += V[ i].adjacencyList.size();
                for( int j = 0; j < V[ i].adjacencyList.size(); ++j) {
                    V[ i].adjacencyList[ j] -= norm;
                }
            }
        }
    }
    
    typedef std::vector<Vertex>::iterator vertices_iterator;
    typedef std::vector<Vertex>::const_iterator vertices_const_iterator;
};


/**
 * @param G graph, may be undirected or directed
 * @param u vertex
 * @param sortedVertices
 */
void depth_first_search( Graph& G, Vertex& u, std::list<Vertex>& sortedVertices) {
    static int time = 0;
    time = time + 1;                           // white vertex u has just
    u.d = time;                                // been discovered
    u.color = Vertex::GRAY;
    BOOST_FOREACH( int idx, G.adjacency( u)) { // explore edge ( u, v)
        Vertex& v = G.V[ idx];
        if( v.color == Vertex::WHITE) {
            v.pi = u.idx;
            depth_first_search( G, v, sortedVertices);
        }
    }
    u.color = Vertex::BLACK;                   // blacken u; it is finished 
    time = time + 1;
    u.f = time;
    sortedVertices.push_front( u);
}

/**
 * complexity O( V + E)
 * @param G graph, may be undirected or directed
 * @param sortedVertices
 */
void depth_first_search( Graph& G, std::list<Vertex>& sortedVertices) {
    BOOST_FOREACH( Vertex u, G.V) {
        u.color = Vertex::WHITE;
        u.pi = -1;
    }
    BOOST_FOREACH( Vertex u, G.V) {
        if( u.color == Vertex::WHITE) {
            depth_first_search( G, u, sortedVertices);
        }
    }    
}


/*
 * 
 */
int main(int argc, char** argv) {

    std::vector<Vertex> vertices;
    std::list<Vertex> sortedVertices;
    for( int i = 0; i < 8; ++i) {
        vertices.push_back( Vertex( i));
    }
    
    vertices[ 0].adjacencyList.push_back( 2);
    vertices[ 0].adjacencyList.push_back( 3);
    vertices[ 1].adjacencyList.push_back( 4);
    vertices[ 1].adjacencyList.push_back( 5);
    vertices[ 2].adjacencyList.push_back( 6);
    vertices[ 3].adjacencyList.push_back( 6);
    vertices[ 4].adjacencyList.push_back( 6);
    vertices[ 3].adjacencyList.push_back( 7);
    vertices[ 4].adjacencyList.push_back( 7);
    
    Graph g( vertices);
    depth_first_search( g, sortedVertices);
    
    for( std::list<Vertex>::const_iterator it = sortedVertices.begin(); it != sortedVertices.end(); ++it) {
        std::cout << ( *it).idx;
    }
    
    return 0;
}

