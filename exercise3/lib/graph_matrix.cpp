#include "graph_matrix.h"
#include <vector>
#include <list>
#include <stack>
#include <iostream>

Graph_Matrix::Graph_Matrix(unsigned int _V, int **_matrix) {
  this->V = _V;
  this->matrix = new int*[this->V];
  for (int i = 0; i < this->V; i++) {
    this->matrix[i] = new int[this->V+3];
    for (int j = 0; j < this->V+3; j++) {
      this->matrix[i][j] = 0;
    }  
  }

  for (int i = 0; i < this->V; i++) {
    this->visited.push_back(false);
    int n,p,b; 
    n=0; p=1; b=2;
    for (int j = 0; j < this->V; j++) {
      if(_matrix[i][j] == 1) {
        this->matrix[i][n] = j+1;
        n = j+3;
      } else if(_matrix[j][i] == 1) {
        this->matrix[i][p] = (p!=1)?-(j+1):j+i;
        p = j+3;
      } else {
        this->matrix[i][b] = (b!=2)?(j+1+this->V):j+1;
        b = j+3;
      }
    }
  }
};

Graph_Matrix::~Graph_Matrix() {
  for (int i = 0; i < this->V; i++) {
    delete[] this->matrix[i];
  }
  delete[] this->matrix;
}

void Graph_Matrix::toposort() {
  for (int i = 0; i < this->V; i++) {
    this->toposort_visit(i);
  }
}

void Graph_Matrix::toposort_visit(int i) {
  if(!this->visited[i]) {
    this->visited[i] = true;
    int j = 0;
    while(this->matrix[i][j]) {
      //printf("matrix[%d][%d]\n",i,j);
      this->toposort_visit(this->matrix[i][j]-1);
      j = this->matrix[i][j]+2;
    }
    this->sorted.push(i);
  }
    
}
  
void Graph_Matrix::print_Sternas_matrix() {
  for (int i = 0; i < this->V; i++) {
    for (int j = 0; j < this->V+3; j++) {
      std::cout << this->matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
