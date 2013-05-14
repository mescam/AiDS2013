#include "graph_gen.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

int **generate_graph(int number_vertices, double k) {
  std::random_device rd;
  std::mt19937 mt(rd());
  int **matrix = new int*[number_vertices];

  for(int i = 0; i < number_vertices; i++)
    matrix[i] = new int[number_vertices]();

  std::vector<int> to_be_cycle(number_vertices + 1);
  for(int i = 0; i < number_vertices; i++)
    to_be_cycle[i] = i;
  std::shuffle(to_be_cycle.begin(), to_be_cycle.end() - 1, mt);
  to_be_cycle[number_vertices] = to_be_cycle[0];

  for(int i = 1; i < number_vertices + 1; i++)
    matrix[to_be_cycle[i - 1]][to_be_cycle[i]] = 1;

  int max_vertices = ceil((number_vertices * (number_vertices - 1) * k) / 2);  
  //kind of filling the graph with essential edges
  
  return matrix;
}

void graph_to_dot(int **matrix, int v) {
  printf("graph {\n");
  for(int i = 0; i < v; i++) {
    for(int j = 0; j < v; j++)
      if(matrix[i][j] != 0)
        printf("%d -- %d;\n", i, j);
  }
  printf("}\n");
}
