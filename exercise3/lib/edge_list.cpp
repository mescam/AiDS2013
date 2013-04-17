#include "edge_list.h"
#include <vector>
#include <stack>
#include <list>

Edge_List::Edge_List(unsigned int _V, int **matrix) {
  this->V = _V;

  for (int i = 0; i < this->V; i++) {
    this->visited.push_back(false);
    for (int j = 0; j < this->V; j++) {
      if(matrix[i][j] == 1) {
        this->edges.push_back(std::make_pair(i,j));
      }
    }
  }
}


void Edge_List::toposort_visit(int i) {
  if(!this->visited[i]) {
    this->visited[i] = true;
    for(auto it = this->edges.begin(); it != this->edges.end(); ++it) {
      if(it->first == i) {
        this->toposort_visit(it->second);
      }
    }
    this->sorted.push(i);
  }
}
  
