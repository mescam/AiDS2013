#include <vector>
#include <list>
#include <iostream>
#include <stack>
#include <algorithm>
#include <ctime>
#include <fstream>

class Graph {
  private:
    std::vector<std::list<int>> adj_list;
    int v;
    float x;
    int curr_edges = 0;
    int max_edges;
    std::stack<int> euler;
    std::vector<int> vertices;
    std::list<std::pair<int, int>> edges;
  std::list<int> hamilton_list;
  std::vector<int> hamilton_cycle_arr;
  int hamilton_first;
  std::vector<bool> visited;
  bool first_cycle = true;

    void generate_first_hammilton() {
      for (int i = 0; i < this->v; i++) {
        vertices.push_back(i);
      }
      std::random_shuffle(vertices.begin(), vertices.end());
      for (int i = 0; i < this->v-1; i++) {
        //this->adj_list[vertices[i]].push_back(vertices[i+1]);
        //this->adj_list[vertices[i+1]].push_back(vertices[i]);
        //printf("Dodaje %d(%d) - %d(%d)\n",vertices[i],i,vertices[i+1],i+1);
        this->add_edge(vertices[i], vertices[i+1]);
        //this->curr_edges++;
      }  
      //this->adj_list[vertices[this->v-1]].push_back(vertices[0]);
      //this->adj_list[vertices[0]].push_back(vertices[this->v-1]);
      //this->curr_edges++;
      //printf("Dodaje %d(0) - %d(%d)\n\n\n",vertices[0],vertices[this->v-1],
        //  this->v-1);
      this->add_edge(vertices[0], vertices[this->v-1]);
    };

    void add_edge(int i, int j){
      std::pair<int, int> e;
      e = std::make_pair(i,j);
      this->adj_list[i].push_back(j);
      this->adj_list[j].push_back(i);
      this->edges.push_back(e);
      this->curr_edges++;
    }

    void add_cycles(){
      //int cycle = 2;
      int cycle = (this->v/2)-1;
      int i;
      int start=0;
      while(this->curr_edges < this->max_edges) {
        /*int cycle = 0.25 * this->v;
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
          this->curr_edges++;*/
        //printf("ruszam od %d z cyklem %d\n",start,cycle);
        i=start;
        do{
          int n = i+cycle;
          n = (n>=this->v)?n-this->v:n;
          //printf("Dodaje %d(%d) - %d(%d)\n",vertices[i],i,vertices[n],n);
          this->add_edge(vertices[i],vertices[n]);
          i=n;
        }while(i!=start);
        start++;
        if(start==cycle) {
          cycle--;
          start=0;
        }
      }
    };
  public:
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

  void dfs_hamilton(int v) {
    if(this->hamilton_list.empty())
      this->hamilton_first = v;

    this->hamilton_list.push_back(v);

    if(this->hamilton_list.size() == this->v) {
      bool is_cycle = false;
      
      for(auto it = this->adj_list[v].begin(); it != this->adj_list[v].end();
          it++) {
        if((*it) == this->hamilton_first) {
          is_cycle = true;
          break;
        }          
      }

      if(is_cycle)
        std::cout << "Cykl ";
      else
        std::cout << "Ścieżka ";

      std::cout << "Hamiltona: ";

      for(auto it = this->hamilton_list.begin(); it != this->hamilton_list.end();
          it++)
        std::cout << (*it) << " ";
      std::cout << "\n";
        
    }
    else {
      this->visited[v] = true;

      for(auto it = this->adj_list[v].begin(); it != this->adj_list[v].end();
          it++)
        if(!this->visited[*it])
          this->dfs_hamilton(*it);

      this->visited[v] = false;
    }

    this->hamilton_list.pop_back();
  };
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

      printf("max: %d; curr: %d\n", max_edges, curr_edges);
    };

    void dot() {
      printf("graph eh{\n");
      for(auto it = this->edges.begin(); it != this->edges.end(); it++) {
        printf("%d -- %d;\n",it->first, it->second);
      }
      printf("}\n");
    };

    void euler_cycle() {
      this->dfs_euler(0);

      printf("curr edges: %d\neuler.size = %d\n\n",this->curr_edges,
          this->euler.size());
      while(!this->euler.empty()) {
        int x = this->euler.top();
        //printf("%d\n",x);
        this->euler.pop();
      }
    };

      // void hamilton_cycle() {
      //   std::fill(this->visited.begin(), this->visited.end(), false);
      //   this->dfs_hamilton(0);
      //   std::cout << "Hamilton cycle: ";

      //   for(auto it = this->hamilton_cycle_arr.begin();
      //       it != this->hamilton_cycle_arr.end(); it++)
      //     std::cout << *it << " ";

      //   std::cout << std::endl;
      // };
};

double timespec_to_miliseconds(timespec *begin, timespec *end) {
  return (double) (end->tv_sec - begin->tv_sec)
    +1.e-9*(end->tv_nsec - begin->tv_nsec);
}

int main(int argc, const char *argv[])
{
  //srand(time(0));
  //Graph g;
  //g.generate_graph(200,0.8);
  //g.dot();
  //printf("\n\n");
  //g.euler_cycle();

  int n[10] = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550};
  //int n[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
  //float x = {0.3, 0.7}
  std::ofstream wynik("res.txt");
  for(int i=0; i<10; i++) {
    timespec begin,end;
    double a,b;
    Graph g1,g2;
    g1.generate_graph(n[i],0.3);
    g2.generate_graph(n[i],0.7);

    printf("euler %d 0.3\n",n[i]);
    clock_gettime(CLOCK_REALTIME, &begin);
    g1.dfs_euler(0);
    clock_gettime(CLOCK_REALTIME, &end);
    a = timespec_to_miliseconds(&begin, &end);
    printf("euler %d 0.7\n",n[i]);
    clock_gettime(CLOCK_REALTIME, &begin);
    g2.dfs_euler(0);
    clock_gettime(CLOCK_REALTIME, &end);
    b = timespec_to_miliseconds(&begin, &end);
    printf("done\n\n");
    wynik << n[i] << " " << a << " " << b << std::endl;
  }
  wynik.close();
  
  return 0;
}



