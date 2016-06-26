/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on April 22, 2014, 6:16 PM
 */

#include <boost/config.hpp> // put this first to suppress some VC++ warnings

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <time.h>

#include <boost/utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/visitors.hpp>

using namespace boost;


struct print_bfs_visitor : public bfs_visitor<> {
  template <class Vertex, class Graph>
  void discover_vertex( Vertex v, Graph&) {
    std::cout << v << " ";
  }
};

struct print_dfs_visitor : public dfs_visitor<> {
  template <class Vertex, class Graph>
  void discover_vertex( Vertex v, Graph&) {
    std::cout << v << " ";
  }
};


struct cycle_detector : public dfs_visitor<>
{
  cycle_detector( bool& has_cycle) 
    : m_has_cycle( has_cycle) { }

  template <class Edge, class Graph>
  void back_edge( Edge, Graph&) { m_has_cycle = true; }

protected:
  bool& m_has_cycle;
};

void resolve_order_dependencies(std::vector< std::vector<int> > const& orders,
        std::vector<int>& sorted_orders) {
    typedef std::pair<int, int> Edge;
    typedef adjacency_list< vecS, vecS, bidirectionalS> Graph;
    const int N = orders.size();

    Graph g( N);
    for ( std::size_t i = 0; i < N; ++i) {
        for  (std::size_t j = 0; j < orders[ i].size(); ++j) {
            /* is is dependent on j, j is used by i */
            add_edge(orders[ i][ j], i, g);
        }
    }

    topological_sort( g, std::back_inserter( sorted_orders));
    std::reverse( sorted_orders.begin(), sorted_orders.end());
}

/*
 * 
 */
int main(int argc, char** argv) {

  std::vector< std::vector<int> > data;
  
  data.push_back( std::vector<int>()); // 0
  
  std::vector<int> v;
  v.push_back( 0);
  v.push_back( 2);
  v.push_back( 4);
  data.push_back( v);                  // 1
  
  data.push_back( std::vector<int>()); // 2
    
  v.clear();
  v.push_back( 1);
  data.push_back( v);                  // 3
  
  data.push_back( std::vector<int>()); // 4
  
  std::vector<int> sorted_orders;
  resolve_order_dependencies( data, sorted_orders);

  typedef std::vector<int> SortedOrders;
  SortedOrders::iterator i;

  std::cout << "make ordering: ";
  for ( i = sorted_orders.begin(); i != sorted_orders.end(); ++i)
      std::cout << *i << " ";
    
  return 0;
}



