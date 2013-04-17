#ifndef GRAPH_MATRIX_H

#define GRAPH_MATRIX_H
#include "graph.h"
#include <vector>
#include <list>
#include <stack>

class Graph_Matrix : public Graph {
  private:
    int **matrix;
    void toposort_visit(int i);
  public:
    Graph_Matrix(unsigned int _V, int **_matrix);
    ~Graph_Matrix();
    void toposort();
    void print_Sternas_matrix();
};


#endif /* end of include guard: GRAPH_MATRIX_H */
