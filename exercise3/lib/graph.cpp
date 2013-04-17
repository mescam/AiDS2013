#include "graph.h"
#include <vector>
#include <list>
#include <stack>
#include <iostream>

void Graph::print_sorted() {
  std::cout << "Sorted order: ";
  while(!this->sorted.empty()) {
    std::cout << this->sorted.top() << " ";
    this->sorted.pop();
  }
  std::cout << std::endl;
}

void Graph::toposort() {
  for (int i = 0; i < this->V; i++) {
    this->toposort_visit(i);
  }
}

void Graph::toposort_visit(int i) {
  return;
}
