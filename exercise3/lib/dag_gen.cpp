#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include "dag_gen.h"

int **dag_gen_matrix(int v) {
  using std::swap;
  int **matrix = new int*[v];

  for(int i = 0; i < v; i++) {
    matrix[i] = new int[v];
  }

  int k_arcs = ceil((v * (v - 1)) / 2 * 0.5);

  while(k_arcs) {
    int a = rand() % v, b = rand() % v;

    if(a != b) {
      if(a > b)
        swap(a, b);
      if(!matrix[a][b]) {
        matrix[a][b]++;
        k_arcs--;
      }
    }
  }

  for(int i = 0; i < v; i++) { 
    int r = rand() % v;

    if(r != i) {
      swap(matrix[i], matrix[r]);
      swap(matrix[i][i], matrix[i][r]);
      swap(matrix[r][r], matrix[r][i]);

      for(int j = 0; j < v; j++)
        if(j != i && j != r)
          swap(matrix[j][i], matrix[j][r]);
    }
  }
  
  return matrix;
}

void dag_gen_dot(int **matrix, int v) {
  printf("digraph {\n");
  for(int i = 0; i < v; i++) {
    for(int j = 0; j < v; j++)
      if(matrix[i][j] != 0)
        printf("%d -> %d;\n", i, j);
  }
  printf("}\n");
}

void dag_gen_print(int **matrix, int v) {
  for(int i = 0; i < v; i++) {
    for(int j = 0; j < v; j++)
      std::cout << matrix[i][j] << " ";
    std::cout << "\n";
  }
}

void dag_gen_free(int **matrix, int v) {
  for(int i = 0; i < v; i++) {
    delete[] matrix[i];
  }

  delete[] matrix;
}

