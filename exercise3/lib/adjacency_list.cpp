#include "adjacency_list.h"
#include <vector>
#include <list>
#include <stack>

Adjacency_List::Adjacency_List(unsigned int _V, int **matrix) {
  this->V = _V;

  for (int i = 0; i < this->V; i++) {
    this->visited.push_back(false); //wasn't visited yet :>
    std::list<int> list; //list of neighbours, will be copied to vector
    for (int j = 0; j < this->V; j++) {
      if(matrix[i][j] == 1) {
        list.push_back(j);
      }
    }
    this->vertices.push_back(list);
  }
}
  
void Adjacency_List::toposort_visit(int i) {
  if(!this->visited[i]) {
    this->visited[i] = true;
    for(auto it = this->vertices[i].begin(); it != this->vertices[i].end();
        ++it) {
      this->toposort_visit(*it);
    }
    this->sorted.push(i);
  }
}

