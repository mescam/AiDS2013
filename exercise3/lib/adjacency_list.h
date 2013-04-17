#ifndef ADJACENCY_LIST_H

#define ADJACENCY_LIST_H
#include "graph.h"
#include <vector>
#include <list>
#include <stack>

class Adjacency_List: public Graph {
  private:
    std::vector<std::list<int>> vertices;
    void toposort_visit(int i); //part of toposort

  public:
    Adjacency_List(unsigned int _V, int **matrix);
    void toposort();
};
#endif /* end of include guard: ADJACENCY_LIST_H */
