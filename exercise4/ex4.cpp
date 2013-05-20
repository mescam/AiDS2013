#include <vector>
#include <list>
#include <iostream>
#include <stack>
#include <algorithm>
#include <ctime>

class Graph {
  private:
    std::vector<std::list<int>> adj_list;
    int v;
    float x;
    int curr_edges = 0;
    int max_edges;
    std::stack<int> euler;

    void generate_first_hammilton() {
      std::vector<int> vertices;
      for (int i = 0; i < this->v; i++) {
        vertices.push_back(i);
      }
      std::random_shuffle(vertices.begin(), vertices.end());
      for (int i = 0; i < this->v-1; i++) {
        this->adj_list[vertices[i]].push_back(vertices[i+1]);
        this->adj_list[vertices[i+1]].push_back(vertices[i]);
        this->curr_edges++;
      }  
      this->adj_list[vertices[this->v-1]].push_back(vertices[0]);
      this->adj_list[vertices[0]].push_back(vertices[this->v-1]);
      this->curr_edges++;
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
          this->adj_list[next].push_back(first);
          cycle--; this->curr_edges++;
          vertex = next;
        }
        this->adj_list[vertex].push_back(first);
        this->adj_list[first].push_back(vertex);
        this->curr_edges++;
      }
    };

    void dfs_euler(int v) {
      while(!this->adj_list[v].empty()) {
        int x = this->adj_list[v].front();
        this->adj_list[v].pop_front();

        for(auto i = this->adj_list[x].begin(); i != this->adj_list[x].end();
            i++) {
          if(*i == v) {
            this->adj_list[x].erase(i);
            break;
          }
        }
        this->dfs_euler(x);
      }
      this->euler.push(v);
    };


  public:
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

    void euler_cycle() {
      this->dfs_euler(0);

      printf("curr edges: %d\neuler.size = %d\n\n",this->curr_edges,
          this->euler.size());
      while(!this->euler.empty()) {
        int x = this->euler.top();
        printf("%d\n",x);
        this->euler.pop();
      }
    }
};

int main(int argc, const char *argv[])
{
  srand(time(0));
  Graph g;
  g.generate_graph(10,0.2);
  //g.dot();
  printf("\n\n\n\n\n");
  g.euler_cycle();
  return 0;
}



