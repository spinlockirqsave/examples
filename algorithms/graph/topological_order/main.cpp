/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 22, 2014, 5:32 PM
 */

#include <boost/config.hpp> // put this first to suppress some VC++ warnings

#include <iostream>
#include <iterator>
#include <algorithm>
#include <time.h>

#include <boost/utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/visitors.hpp>

using namespace std;
using namespace boost;

enum files_e { dax_h, yow_h, boz_h, zow_h, foo_cpp, 
               foo_o, bar_cpp, bar_o, libfoobar_a,
               zig_cpp, zig_o, zag_cpp, zag_o, 
                 libzigzag_a, killerapp, N };
                 
const char* name[] = { "dax.h", "yow.h", "boz.h", "zow.h", "foo.cpp",
                       "foo.o", "bar.cpp", "bar.o", "libfoobar.a",
                       "zig.cpp", "zig.o", "zag.cpp", "zag.o",
                       "libzigzag.a", "killerapp" };


struct print_bfs_visitor : public bfs_visitor<> {
  template <class Vertex, class Graph>
  void discover_vertex( Vertex v, Graph&) {
    cout << name[ v] << " ";
  }
};

struct print_dfs_visitor : public dfs_visitor<> {
  template <class Vertex, class Graph>
  void discover_vertex( Vertex v, Graph&) {
    cout << name[ v] << " ";
  }
};


struct cycle_detector : public dfs_visitor<>
{
  cycle_detector(bool& has_cycle) 
    : m_has_cycle(has_cycle) { }

  template <class Edge, class Graph>
  void back_edge(Edge, Graph&) { m_has_cycle = true; }
protected:
  bool& m_has_cycle;
};

/*
 * 
 */
int main(int argc, char** argv) {

      typedef pair<int,int> Edge;
  Edge used_by[] = {
    Edge(dax_h, foo_cpp), Edge(dax_h, bar_cpp), Edge(dax_h, yow_h),
    Edge(yow_h, bar_cpp), Edge(yow_h, zag_cpp),
    Edge(boz_h, bar_cpp), Edge(boz_h, zig_cpp), Edge(boz_h, zag_cpp),
    Edge(zow_h, foo_cpp), 
    Edge(foo_cpp, foo_o),
    Edge(foo_o, libfoobar_a),
    Edge(bar_cpp, bar_o),
    Edge(bar_o, libfoobar_a),
    Edge(libfoobar_a, libzigzag_a),
    Edge(zig_cpp, zig_o),
    Edge(zig_o, libzigzag_a),
    Edge(zag_cpp, zag_o),
    Edge(zag_o, libzigzag_a),
    Edge(libzigzag_a, killerapp)
  };
  const std::size_t nedges = sizeof(used_by)/sizeof(Edge);

  typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  // VC++ can't handle the iterator constructor
  Graph g(N);
  for (std::size_t j = 0; j < nedges; ++j) {
    graph_traits<Graph>::edge_descriptor e; bool inserted;
    boost::tie(e, inserted) = add_edge(used_by[j].first, used_by[j].second, g);
  }
#else
  Graph g(used_by, used_by + nedges, N);
#endif
  typedef graph_traits<Graph>::vertex_descriptor Vertex;

  // Determine ordering for a full recompilation
  // and the order with files that can be compiled in parallel
  {
    typedef list<Vertex> MakeOrder;
    MakeOrder::iterator i;
    MakeOrder make_order;

    topological_sort(g, std::front_inserter(make_order));
    cout << "make ordering: ";
    for (i = make_order.begin();
         i != make_order.end(); ++i) 
      cout << name[*i] << " ";
  
    cout << endl << endl;
  }
    
    return 0;
}

