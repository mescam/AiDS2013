#ifndef EDGE_LIST_H

#define EDGE_LIST_H
#include "graph.h"
#include <vector>
#include <list>
#include <stack>

class Edge_List : public Graph {
  private:
    std::vector<std::pair<int, int>> edges;
    void toposort_visit(int i);

  public:
    Edge_List(unsigned int _V, int **matrix);
    void toposort();

};

#endif /* end of include guard: EDGE_LIST_H */
