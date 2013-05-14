#ifndef ADJ_LIST_H_

#define ADJ_LIST_H_

#include <vector>
#include <list>
#include <stack>

class Adjacency_List {
private:
  std::vector<bool> visited;
  std::vector<std::list<int>> vertices;
  std::stack<int> cycle;
  unsigned int V;

public:
  Adjacency_List(unsigned int _V, int **matrix);
  void euler_cycle(int vertex);
  void print_cycle();
};

#endif
