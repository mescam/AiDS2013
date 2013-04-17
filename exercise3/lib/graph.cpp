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
  std::cout << "not implemented yet" << std::endl;
}
