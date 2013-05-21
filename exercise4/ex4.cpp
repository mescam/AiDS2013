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
    std::vector<bool> visited;
    bool first_cycle = true;

    bool is_connected(int i, int j) {
      for(auto it = this->adj_list[i].begin(); it!=this->adj_list[i].end(); it++) {
        if ((*it)==j)
          return true;
      }
      return false;
    }


    void generate_first_hamilton() {
      for (int i = 0; i < this->v; i++) {
        vertices.push_back(i);
      }
      std::random_shuffle(vertices.begin(), vertices.end());
      for (int i = 0; i < this->v-1; i++) {
        this->add_edge(vertices[i], vertices[i+1]);
      }  
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
      int cycle=2;
      //for(cycle=2; cycle<this->v; cycle++) {
      //  if(this->v % cycle == 0) break;
      //}
      //int add = (this->v%cycle==0)?1:0
      int i;
      int start=0;
      while(this->curr_edges < this->max_edges && cycle<(this->v/2)) {
        i=start;
        do{
          int n = i+cycle;
          //if(this->is_connected(i,n)) break;
          n = (n>=this->v)?n-this->v:n;
          if(this->is_connected(vertices[i],vertices[n])) break;
          this->add_edge(vertices[i],vertices[n]);
          i=n;
        }while(i!=start);

        //if(add) start++; else start=cycle;
        start++;
        if(start==cycle) {
          cycle++;
          start=0;
        }
      }
    };

  public:
    int hamilton_first = 0;

    void isolate() {
      int n = this->v-1;
      for(auto it=this->adj_list.begin(); it!= this->adj_list.end(); it++) {
        it->remove(n);
      }
      this->adj_list[n].clear();
    }

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
    void prepare_to_hamilton() {
      this->visited.resize(this->v);
      std::fill(this->visited.begin(), this->visited.end(), false);
    }

    void dfs_hamilton(int v, long sec) {
      if(static_cast<long>(time(0)) - sec > 2) {
        this->hamilton_first = 1;
        std::cout << "time limit exceeded\n";
        return;
      }
      //printf("lol?\n");

      if(this->hamilton_first==1) return;

      this->hamilton_list.push_back(v);

      if(this->hamilton_list.size() == this->v) {
        bool is_cycle = false;

        for(auto it = this->adj_list[v].begin(); it != this->adj_list[v].end();
            it++) {
          if((*it) == 0) {
            is_cycle = true;
            //printf("mam, spadam\n");
            this->hamilton_first=1;
            break;
          }          
        }
      } else {
        this->visited[v] = true;

        for(auto it = this->adj_list[v].begin(); it != this->adj_list[v].end();
            it++)
          if(!this->visited[*it]){
            if(this->hamilton_first==1) return;
            this->dfs_hamilton(*it, sec);
          }

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

      this->generate_first_hamilton();
      this->add_cycles();
      for(auto it = this->adj_list.begin(); it!=this->adj_list.end(); ++it){ 
        //std::sort(it->begin(), it->end());
        it->sort();
        if(it->size()%2!=0) printf("NO NIE!\n\n");
      }
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

};

double timespec_to_miliseconds(timespec *begin, timespec *end) {
  return (double) (end->tv_sec - begin->tv_sec)
    +1.e-9*(end->tv_nsec - begin->tv_nsec);
}

void hamilton2(){
  int n[10] = {2,4,6,8,10,12,14,16,18,20};

  std::ofstream wynik("res3.txt");
  for(int i=0; i<10; i++) {
    timespec begin, end;
    double a=0;

    for(int j=0; j<1; j++) {
      Graph g;
      g.generate_graph(n[i],0.5);
      g.prepare_to_hamilton();
      if(rand()%2==0) g.isolate();

      printf("hamilton full %d\n",n[i]);
      clock_gettime(CLOCK_REALTIME, &begin);
      g.dfs_hamilton(0, std::time(0));
      clock_gettime(CLOCK_REALTIME, &end);
      printf("done\n\n");
      a+=timespec_to_miliseconds(&begin, &end);
    }
    a/=1;
    wynik << n[i] << " " << a << std::endl;
  }
  wynik.close();
}

void euler(){
  int n[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
  //float x = {0.3, 0.7}
  std::ofstream wynik("res.txt");
  for(int i=0; i<10; i++) {
    timespec begin,end;
    double a,b;
    a=b=0;
    for(int j=0; j<10; j++) {
      Graph g1,g2;
      g1.generate_graph(n[i],0.3);
      g2.generate_graph(n[i],0.7);
      printf("euler %d 0.3\n",n[i]);
      clock_gettime(CLOCK_REALTIME, &begin);
      g1.dfs_euler(0);
      clock_gettime(CLOCK_REALTIME, &end);
      a += timespec_to_miliseconds(&begin, &end);
      printf("euler %d 0.7\n",n[i]);
      clock_gettime(CLOCK_REALTIME, &begin);
      g2.dfs_euler(0);
      clock_gettime(CLOCK_REALTIME, &end);
      b += timespec_to_miliseconds(&begin, &end);
      printf("done\n\n");
    }
    a/=10; b/=10;
    wynik << n[i] << " " << a << " " << b << std::endl;
  }
  wynik.close();
}

void hamilton1() {
#define TESTS 3
  //int n[10] = {4, 6, 8, 10, 12, 14, 16, 18, 20, 22};
  int n[10] = {100, 200, 300, 400, 500, 600, 700, 800, 1000};
  std::ofstream wynik("res2.txt");
  for(int i=0; i<10; i++) {
    double a,b;
    a=b=0;
    for(int j=0; j<TESTS; j++) {
      Graph g1, g2;
      timespec begin, end;
      //g1.hamilton_first=1;
      //g2.hamilton_first=1;
      g1.generate_graph(n[i]/10, 0.3);
      g2.generate_graph(n[i], 0.7);
      g1.prepare_to_hamilton();
      g2.prepare_to_hamilton();

      printf("hamilton %d 0.3 #%d\n",n[i],j);
      clock_gettime(CLOCK_REALTIME, &begin);
      g1.dfs_hamilton(0, static_cast<long>(time(0)));
      clock_gettime(CLOCK_REALTIME, &end);
      a+=timespec_to_miliseconds(&begin, &end);

      printf("hamilton %d 0.7 #%d\n",n[i],j);
      clock_gettime(CLOCK_REALTIME, &begin);
      g2.dfs_hamilton(0, static_cast<long>(time(0)));
      clock_gettime(CLOCK_REALTIME, &end);
      b+=timespec_to_miliseconds(&begin, &end);

      printf("done\n\n");
    }
    a/=TESTS;
    b/=TESTS;
    wynik << n[i] << " " << a << " " << b << std::endl;
  }
  wynik.close();

}

int main(int argc, const char *argv[])
{
  srand(time(0));

  /* Graph g;
     g.generate_graph(10, 0.7);
     g.dot();
     */
  ///printf("%ld\n\n",static_cast<int>(time(0)));
  switch(argv[1][0]) {
    case '1':
      euler();
      break;
    case '2':
      hamilton1();
      break;
    case '3':
      hamilton2();
      break;
  }
  return 0;
}



