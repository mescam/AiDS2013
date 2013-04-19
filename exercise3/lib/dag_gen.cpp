#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include "dag_gen.h"
#include <list>

int **dag_gen_matrix2(int v) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> ldist(1,50);
  std::uniform_int_distribution<> pdist(1,100);

  int **matrix = new int*[v];
  std::vector<int> layers(v);

  for(int i = 0; i < v; i++)
    matrix[i] = new int[v]();

  for(int &v : layers)
    v = ldist(mt);

  for(int i = 0; i < v; i++)
    for(int j = 0; j < v; j++)
      if(layers[i] < layers[j]) {
        int shot = pdist(mt);

        if(shot < 50)
          matrix[i][j] = 1;
        else
          matrix[i][j] = 0;
      }

  return matrix;
}

int **dag_gen_matrix(int v) {
  using std::swap;
  int **matrix = new int*[v];

  for(int i = 0; i < v; i++) {
    matrix[i] = new int[v];

    for(int j = 0; j < v; j++) matrix[i][j] = 0;
  }

  //printf("after1\n");

  int k_arcs = ceil((v * (v - 1)) / 2 * 0.5);
  //printf("k_arcs = %d\n",k_arcs);
  while(k_arcs) {
    int a = rand() % v, b = rand() % v;

    if(a != b) {
      //printf("wbilem!\n");
      if(a > b) {
        //printf("swap\n");
        swap(a, b);
      }
      if(!matrix[a][b]) {
        matrix[a][b]++;
        k_arcs--;
        //printf("zmniejszam!\n");
      }
    }
  }

  //printf("after while\n");

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

  //printf("after for\n");

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

std::list<int> bfs_unconnected(int **matrix, int v) {
  std::vector<int> unconnected;
  bfs_queue queue;
  std::list<int> return_unconnected;

  queue.push(0);
  unconnected.resize(v);
  std::fill(unconnected.begin(), unconnected.end(), true);

  while(!queue.empty()) {
    int u = queue.front();
    queue.pop();
    //printf("n=%d u=%d vector.size()=%d\n",v,u,unconnected.size());
    unconnected[u] = false;
    for(int i = 0; i < v; i++) {
      //printf("test1\n");
      if(matrix[u][i] == 1 && unconnected[i]) {
        queue.push(i);
      }
    }
  }

  for(auto it = unconnected.begin(); it != unconnected.end(); it++) {
    if(*it == false)
      return_unconnected.push_front(it-unconnected.begin());
  }
    
  return return_unconnected;
}
