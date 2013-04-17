#ifndef ADJACENCY_MATRIX_H

#define ADJACENCY_MATRIX_H

#include "graph.h"
#include <list>
#include <vector>
#include <stack>

class Adjacency_Matrix : public Graph {
  private:
    void toposort_visit(int i);
    int **matrix;
  public:
    Adjacency_Matrix(unsigned int _V, int **_matrix);
    void toposort();
};

#endif /* end of include guard: ADJACENCY_MATRIX_H */
