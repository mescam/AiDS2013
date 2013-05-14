#include "adj_list.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>

Adjacency_List::Adjacency_List(unsigned int _V, int **matrix) {
  this->V = _V;

  for (int i = 0; i < this->V; i++) {
    this->visited.push_back(false); //wasn't visited yet :>
    std::list<int> list; //list of neighbours, will be copied to vector
    for (int j = 0; j < this->V; j++) {
      if(matrix[i][j] == 1) {
        list.push_back(j);
      }
    }
    this->vertices.push_back(list);
  }
}

void Adjacency_List::dfs_euler_cycle(int vertex) {
  while(!this->vertices[vertex].empty()) {
    int e = this->vertices[vertex].front();
    this->vertices[vertex].pop_front();

    for(auto it = this->vertices[e].begin(); it != this->vertices[e].end(); it++)
      if(vertex == (*it)) {
        this->vertices[e].erase(it);
        break;
      }
    this->dfs_euler_cycle(e);
  }

  this->euler_stack.push(vertex);
}

void Adjacency_List::dfs_hamilton_cycle(int vertex) {
  if(this->hamilton_list.empty())
    this->hamilton_first = vertex;
  
  this->hamilton_list.push_back(vertex);

  if(this->hamilton_list.size() != this->V) {
    this->visited[vertex] = true;

    for(auto it = this->vertices[vertex].begin(); it != this->vertices[vertex].end(); it++)
      if(!this->visited[(*it)])
        this->dfs_hamilton_cycle(*it);

    this->visited[vertex] = false;
  }
  else {
    bool is_cycle = false;

    for(auto it = this->vertices[vertex].begin(); it != this->vertices[vertex].end(); it++)
      if(this->hamilton_first == (*it)) {
        is_cycle = true;
        break;
      }

    if(is_cycle) {
      if(this->first_cycle) {
        for(auto it = this->hamilton_list.begin(); it != this->hamilton_list.end(); it++)
          this->hamilton_cycle_arr.push_back(*it);

        return;
      }
      else
      {
        std::cout << "Hamilton cycle: ";
        for(auto it = this->hamilton_list.begin(); it != this->hamilton_list.end(); it++)
          std::cout << *it << " ";

        std::cout << std::endl;
      }
    }
  }

  this->hamilton_list.pop_back();
}

void Adjacency_List::euler_cycle() {
  //Activate commented parts to call euler_cycle several times
  /*while(!this->euler_stack.empty())
    this->euler_stack.pop();

  auto temp_vert = this->vertices;
  */
  this->dfs_euler_cycle(0);
  std::cout << "Euler cycle: ";
  while(!this->euler_stack.empty()) {
    std::cout << this->euler_stack.top() << " ";
    this->euler_stack.pop();
  }
  std::cout << std::endl;

//  this->vertices = temp_vert;
}

void Adjacency_List::hamilton_cycle() {
  //Activate commented parts to call hamilton_cycle several times
  //std::fill(this->visited.begin(), this->visited.end(), false);
  this->dfs_hamilton_cycle(0);
  std::cout << "Hamilton cycle: ";

  for(auto it = this->hamilton_cycle_arr.begin(); it != this->hamilton_cycle_arr.end(); it++)
    std::cout << *it << " ";

  std::cout << std::endl;
}

void Adjacency_List::set_first_cycle(bool is) {
  this->first_cycle = is;
}
