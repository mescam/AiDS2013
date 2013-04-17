#include "adjacency_matrix.h"
#include <list>
#include <vector>
#include <stack>

Adjacency_Matrix::Adjacency_Matrix(unsigned int _V, int **_matrix) {
  this->matrix = _matrix;
  this->V = _V;
  this->visited.resize(this->V);
  std::fill(this->visited.begin(), this->visited.end(), false);
}

void Adjacency_Matrix::toposort_visit(int i) {
  if(!this->visited[i]) {
    this->visited[i] = true;
    for (int j = 0; j < this->V; j++) {
      if(this->matrix[i][j] == 1) {
        this->toposort_visit(j);
      }
    }
    this->sorted.push(i);
  }
}
    
  
