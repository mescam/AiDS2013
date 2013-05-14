#ifndef ADJ_LIST_H_

#define ADJ_LIST_H_

#include <vector>
#include <list>
#include <stack>

class Adjacency_List {
private:
  std::vector<bool> visited;
  std::vector<std::list<int>> vertices;
  std::stack<int> euler_stack;
  std::list<int> hamilton_list;
  std::vector<int> hamilton_cycle_arr;
  int hamilton_first;
  bool first_cycle = true; //break after first cycle found
  unsigned int V;
  void dfs_hamilton_cycle(int vertex);
  void dfs_euler_cycle(int vertex);

public:
  Adjacency_List(unsigned int _V, int **matrix);
  void set_first_cycle(bool is);
  void euler_cycle();
  void hamilton_cycle();
};

#endif
