#include "lib/adj_list.h"
#include "lib/graph_gen.h"

#include <iostream>

int main() {
  auto matrix = generate_graph(20,0.3);

  auto lst = new Adjacency_List(20,matrix);
  lst->euler_cycle(0);
  lst->print_cycle();

  //no destroying of generated matrix, how baaad, TODO
  
  return 0;
}
