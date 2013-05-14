#include "lib/adj_list.h"
#include "lib/graph_gen.h"

#include <iostream>

int main() {
  auto matrix = generate_graph(10,0.3);

  auto lst = new Adjacency_List(10,matrix);
  lst->hamilton_cycle();
  lst->euler_cycle();
  
  //no destroying of generated matrix, how baaad, TODO
  
  return 0;
}
