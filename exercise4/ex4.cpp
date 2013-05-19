#include <vector>
#include <list>
#include <iostream>
#include <stack>
#include <algorithm>
#include <ctime>

class Graph {
  private:
    void generate_first_hammilton() {
      std::vector<int> vertices;
      for (int i = 0; i < this->v; i++) {
        vertices.push_back(i);
      }
      std::random_shuffle(vertices.begin(), vertices.end());
      for (int i = 0; i < this->v-1; i++) {
        this->adj_list[vertices[i]].push_back(vertices[i+1]);
        this->curr_edges++;
      }  
      this->adj_list[vertices[this->v-1]].push_back(vertices[0]);
    };

    void add_cycles(){
      while(this->curr_edges < this->max_edges) {
        int cycle = 0.25 * this->v;
        cycle=(cycle>(this->max_edges - this->curr_edges))?(this->max_edges-
            this->curr_edges):cycle;

        int vertex;
        int first = vertex = rand()%this->v;
        while(cycle-1) {
          int next;
          do{
            next = rand()%this->v;
          }while(next==vertex);
          this->adj_list[vertex].push_back(next);
          cycle--; this->curr_edges++;
          vertex = next;
        }
        this->adj_list[vertex].push_back(first);
        this->curr_edges++;
      }
    }

  public:
    std::vector<std::list<int>> adj_list;
    int v;
    float x;
    int curr_edges = 0;
    int max_edges;

    void generate_graph(int _v, float _x) {
      this->v = _v;
      this->x = _x;
      this->max_edges = (_v*(_v-1)/2)*_x;

      for (int i = 0; i < this->v; i++) {
        std::list<int> a;
        this->adj_list.push_back(a);
      }

      this->generate_first_hammilton();
      this->add_cycles();
    };

    void dot() {
      printf("graph eh{\n");
      for(int i = 0; i < this->v; i++) 
        for(auto it = this->adj_list[i].begin(); it != this->adj_list[i].end();
            it++) 
          printf("%d -- %d;\n",i,*it);
      printf("}\n");
    };
};

int main(int argc, const char *argv[])
{
  Graph g;
  g.generate_graph(10,0.7);
  g.dot();
  return 0;
}


      