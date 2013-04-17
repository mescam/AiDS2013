#ifndef GRAPH_H

#define GRAPH_H

#include <vector>
#include <list>
#include <stack>
#include <iostream>

class Graph {
  protected:
    std::stack<int> sorted;
    std::vector<bool> visited;
    unsigned int V;

  public:
    virtual void toposort();
    void print_sorted();
};




#endif /* end of include guard: GRAPH_H */
