/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 22, 2014, 10:53 PM
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
    int d;
    int pi;
    std::vector<int> adjacencyList;
    explicit Vertex() : color( WHITE), d( -1), pi( -1), idx( -1) {}
    explicit Vertex( int idx) : idx( idx), color( WHITE), d( -1), pi( -1) {}
    int idx;
};

struct Graph {
    /* sorted vector of vertices*/
    std::vector<Vertex> V;
    
    /* number of vertices*/
    int const N;
    
    std::vector<int> const& adjacency( Vertex const& u) const {
        return V[ u.idx].adjacencyList;
    }
    
    static bool verticesCompare( Vertex const& lhs, Vertex const& rhs) {
        return lhs.idx < rhs.idx;
    }
    
    /**
     * Constructor with invariant: graph contains normalized
     * vector of vertices with normalized indices and adjacency lists
     * N is number of vertices in graph
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
 * 
 * @param G graph
 * @param s root vertex
 */
void breadth_first_search( Graph& G, Vertex& s) {
    BOOST_FOREACH( Vertex u, G.V) {
        u.color = Vertex::WHITE;
        u.d = -1;
        u.pi = -1;
    }
    s.color = Vertex::GRAY;
    s.d = -1;
    s.pi = -1;
    std::queue<Vertex> Q;
    Q.push( s);
    while( !Q.empty()) {
        Vertex& u = Q.front();
        Q.pop();
        BOOST_FOREACH( int idx, G.adjacency( u)) {
            Vertex& v = G.V[ idx];
            if( v.color == Vertex::WHITE) {
                v.color = Vertex::GRAY;
                v.d = u.d + 1;
                v.pi = u.idx;
                Q.push( v);
            }
        }
        u.color = Vertex::BLACK;
    }
}
/*
 * 
 */
int main(int argc, char** argv) {

    std::vector<Vertex> vertices;
    for( int i = 0; i < 8; ++i) {
        vertices.push_back( Vertex( i + 1)); // 1, 2, ..., 8
    }
    
    vertices[ 0].adjacencyList.push_back( 2);
    vertices[ 0].adjacencyList.push_back( 3);
    vertices[ 1].adjacencyList.push_back( 4);
    vertices[ 1].adjacencyList.push_back( 5);
    vertices[ 2].adjacencyList.push_back( 6);
    vertices[ 3].adjacencyList.push_back( 7);
    vertices[ 4].adjacencyList.push_back( 7);
    vertices[ 3].adjacencyList.push_back( 8);
    vertices[ 4].adjacencyList.push_back( 8);
    
    Graph g( vertices);
    breadth_first_search( g, g.V[ 0]);
    
    return 0;
}

