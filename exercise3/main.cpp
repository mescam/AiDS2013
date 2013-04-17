#include "lib/adjacency_list.h"
#include "lib/edge_list.h"
#include "lib/adjacency_matrix.h"
#include "lib/graph_matrix.h"
#include <iostream>

//clang++ -std=c++11 lib/graph.cpp lib/adjacency_list.cpp main.cpp -o graphs
int main(int argc, const char *argv[])
{
  int **matrix;

  matrix = new int*[5];
  for (int i = 0; i < 5; i++) {
    matrix[i] = new int[5];
    for (int j = 0; j < 5; j++) {
      matrix[i][j] = 0;
    }
    
  }
  ///god will hate me
  matrix[0][1]=matrix[0][2]=matrix[0][3]=matrix[1][4]=matrix[2][3]=
    matrix[3][1]=1;

  std::cout << "Adjacency list: " << std::endl;
  Adjacency_List adj_list(5, matrix);
  adj_list.toposort();
  adj_list.print_sorted();
  std::cout << "----------------" << std::endl;

  std::cout << "Edge list: " << std::endl;
  Edge_List e_list(5, matrix);
  e_list.toposort();
  e_list.print_sorted();
  std::cout << "----------------" << std::endl;

  std::cout << "Adjacency matrix: " << std::endl;
  Adjacency_Matrix adj_mat(5, matrix);
  adj_mat.toposort();
  adj_mat.print_sorted();
  std::cout << "----------------" << std::endl;


  std::cout << "Graph matrix: " << std::endl;
  Graph_Matrix gmat(5, matrix);
  //gmat.print_Sternas_matrix();
  gmat.toposort();
  gmat.print_sorted();
  std::cout << "----------------" << std::endl;


  for (int i = 0; i < 5; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  
  return 0;
}
