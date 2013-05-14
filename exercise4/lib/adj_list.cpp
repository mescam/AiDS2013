#include "adj_list.h"
#include <iostream>
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

void Adjacency_List::euler_cycle(int vertex) {
  while(!this->vertices[vertex].empty()) {
    int e = this->vertices[vertex].front();
    this->vertices[vertex].pop_front();

    for(auto it = this->vertices[e].begin(); it != this->vertices[e].end(); it++)
      if(vertex == (*it)) {
        this->vertices[e].erase(it);
        break;
      }
    this->euler_cycle(e);
  }

  this->cycle.push(vertex);
}

void Adjacency_List::print_cycle() {
  std::cout << "Euler cycle: ";
  while(!this->cycle.empty()) {
    std::cout << this->cycle.top() << " ";
    this->cycle.pop();
  }
  std::cout << std::endl;
}
