/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 23, 2014, 2:42 AM
 */

#include <stdio.h>
#include <vector>
#include <list>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <limits>

#include <boost/foreach.hpp>

struct Vertex {
    enum Color { WHITE, GRAY, BLACK};
    int color;
    int d; // time of discovery
    int f; // time of finish
    int pi;
    std::vector<int> adjacencyList;
    int idx;
    
    explicit Vertex( int idx = -1) : idx( idx), color( WHITE), d( -1), f( -1), pi( -1) {}
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
    
    static int idx( Vertex const& u) { return u.idx;}
    
    void normalizeDependenciesLists( int norm) {
        
        /* normalize dependencies to start from 0 */
            for( int i = 0; i < N; ++i) {
                
                E += V[ i].adjacencyList.size();
                for( int j = 0; j < V[ i].adjacencyList.size(); ++j) {
                    V[ i].adjacencyList[ j] -= norm;
                }
            }
    }

    /**
     * Constructor with invariant: graph contains normalized
     * vector of vertices with normalized indices and adjacency lists
     * @param v vertices
     */
    explicit Graph( std::vector<Vertex>& v) : V( v), N( v.size()), E( 0) {

        std::sort( V.begin(), V.end(), &verticesCompare);
        
        /* check for duplicates */
        if( V[ N - 1].idx != V[ 0].idx + N - 1)
            throw std::runtime_error( "incorrect indices: duplicates");
        int idxNorm = V[ 0].idx;
        
        /* normalize indices to start from 0 */
        if( V[ 0].idx != 0) {
            for( int i = 0; i < N; ++i) {
                
                E += V[ i].adjacencyList.size();
                for( int j = 0; j < V[ i].adjacencyList.size(); ++j) {
                    
                    /* range check for dependencies specifications */
                    if( V[ i].adjacencyList[ j] < idxNorm || V[ N - 1].idx < V[ i].adjacencyList[ j])
                        throw std::runtime_error( "incorrect indices: dependencies list");
                    V[ i].adjacencyList[ j] -= idxNorm;
                }
                
                V[ i].idx -= idxNorm;
            }
        }
        if( V[ N - 1].idx != N - 1) throw std::runtime_error( "incorrect indices");
    }
    
    /**
     * Constructor with invariant: graph contains normalized
     * vector of vertices with normalized indices and adjacency lists
     * note: if dependencies[ u] contains v as a dependency then v
     * should be placed before u, this means that ( v, u) edge has
     * to be inserted into graph: V[ v] has adjacency V[ u]
     * other notation is: V[ u] is "used by" V[ v], V[ v] is dependent on V[ u]
     * @param dependencies array of tasks to be ordered
     */
    explicit Graph( std::vector<std::vector<int> > const& dependencies)
                  : N( dependencies.size()), V( dependencies.size()), E( 0) {
        int adjMin = std::numeric_limits<int>::max();
        int adjMax = std::numeric_limits<int>::min();
        for( int i = 0; i < N; ++i) {
            V[ i].idx = i;
            E += dependencies[ i].size();

            for( int j = 0; j < dependencies[ i].size(); ++j) {
                
                /* V[ [ i, j]] has adjacency i */
                V[ dependencies[ i][ j] ].adjacencyList.push_back( i);
                adjMin = std::min( adjMin, dependencies[ i][ j]);
                adjMax = std::max( adjMax, dependencies[ i][ j]);
            }
        }
        if( E > 0)
            if( adjMax - adjMin != N - 1) throw std::runtime_error( "incorrect indices: dependencies list");
        if( adjMin != 0) normalizeDependenciesLists( adjMin);
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
        
        /* cyclic dependency check */
        if( v.color == Vertex::GRAY)
            throw std::runtime_error( "cyclic dependency");
        
        if( v.color == Vertex::WHITE) {
            v.pi = u.idx;
            depth_first_search( G, v, sortedVertices);
        }
    }
    
    u.color = Vertex::BLACK;                   // blacken u; it is finished 
    time = time + 1;
    u.f = time;
    sortedVertices.push_front( u);             // insert into list of ordered vertices
}

/**
 * complexity O( V + E)
 * since it take O( V + E) to perform depth first search
 * and O( 1) time to insert each of the |V| vertices onto
 * the front of the linked list
 * @param G graph, may be undirected or directed
 * @param sortedVertices list sorted topologically by this procedure
 */
void depth_first_search( Graph& G, std::list<Vertex>& sortedVertices) {
    BOOST_FOREACH( Vertex& u, G.V) {
        u.color = Vertex::WHITE;
        u.pi = -1;
    }
    BOOST_FOREACH( Vertex& u, G.V) {
        if( u.color == Vertex::WHITE) {
            depth_first_search( G, u, sortedVertices);
        }
    }    
}

void topological_sort( Graph& G, std::list<Vertex>& sortedVertices) {
    depth_first_search( G, sortedVertices);
}

void topological_sort_and_reverse(
                Graph& G, std::list<Vertex>& sortedVertices) {
    depth_first_search( G, sortedVertices);
    std::reverse( sortedVertices.begin(), sortedVertices.end());
}

/**
 * 
 * @param ordersDependencies array of tasks to be ordered
 * @param sortedOrders result ordered by dfs according to dependencies
 *        such that if u contains v as a dependency then v is placed
 *        before u
 */
void resolve_orders_dependencies(
                std::vector<std::vector<int> > const& ordersDependencies,
                std::vector<int>& sortedOrders) {
    
    Graph g( ordersDependencies);
    
    std::list<Vertex> sortedList;
    topological_sort( g, sortedList);
    
    sortedOrders.resize( sortedList.size());
    std::transform( sortedList.begin(), sortedList.end(),
                        sortedOrders.begin(), Graph::idx);
}

/*
 * 
 */
int main(int argc, char** argv) {
    {
        std::vector<Vertex> vertices;
        std::list<Vertex> sortedVertices;
        for ( int i = 0; i < 8; ++i) {
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
        topological_sort( g, sortedVertices);

        for ( std::list<Vertex>::const_iterator it = sortedVertices.begin();
                it != sortedVertices.end(); ++it) {
            std::cout << ( *it).idx;
        }
    }

    {
        std::cout << std::endl;
        std::vector<Vertex> vertices;
        std::list<Vertex> sortedVertices;
        for ( int i = 0; i < 3; ++i) {
            vertices.push_back( Vertex( i));
        }

        vertices[ 1].adjacencyList.push_back( 0); // 1 is "used by" 0
        vertices[ 1].adjacencyList.push_back( 2); // 1 is "used by" 2

        Graph g( vertices);
        topological_sort( g, sortedVertices);

        for ( std::list<Vertex>::const_iterator it = sortedVertices.begin();
                it != sortedVertices.end(); ++it) {
            std::cout << ( *it).idx;
        }
    }
    
    {
        std::cout << std::endl;
        std::vector<std::vector<int> > array(3);
        std::vector<int> sortedOrders;

        array[ 1].push_back( 0); // 1 "is dependent on" 0
        array[ 1].push_back( 2); // 1 "is dependent on" 2

        try {
            resolve_orders_dependencies( array, sortedOrders);
        } catch ( std::exception& e) {
            std::cout << e.what();
            // search for cyclic dependencies
            // remove
            // resolve_orders_dependencies( array, sortedOrders);
        }

        for ( std::vector<int>::const_iterator it = sortedOrders.begin();
                it != sortedOrders.end(); ++it) {
            std::cout << ( *it);
        }
    }
    
    {
        std::cout << std::endl;
        std::vector<std::vector<int> > array(3);
        std::vector<int> sortedOrders;

        array[ 1].push_back( 0); // 1 "is dependent on" 0
        array[ 1].push_back( 2); // 1 "is dependent on" 2
        array[ 2].push_back( 1); // but 2 "is dependent" on 1...

        try {
            resolve_orders_dependencies( array, sortedOrders);
        } catch ( std::exception& e) {
            std::cout << e.what();
            // search for cyclic dependencies
            // remove
            // resolve_orders_dependencies( array, sortedOrders);
        }

        for ( std::vector<int>::const_iterator it = sortedOrders.begin();
                it != sortedOrders.end(); ++it) {
            std::cout << ( *it);
        }
    }
    
    return 0;
}

