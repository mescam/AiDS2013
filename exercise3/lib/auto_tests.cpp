#include "adjacency_list.h"
#include "adjacency_matrix.h"
#include "edge_list.h"
#include "graph_matrix.h"
#include "dag_gen.h"
#include <fstream>
#include <ctime>

#define TESTS 1

double timespec_to_miliseconds(timespec *begin, timespec *end) {
  return (double) (end->tv_sec - begin->tv_sec)+1.e-9*(end->tv_nsec - begin->tv_nsec);
}

void auto_test_flow() {
  
  std::ofstream output("tests/results.txt");
  for (int n = 0; n < 50; n+=10) {
    output << n;
    double results[4] = {0,0,0,0};

    for (int test = 0; test < TESTS; test++) { 
      printf("Generating matrix n=%d, test #%d\n", n, test);
      auto matrix = dag_gen_matrix(n);
      printf("Done! \n");
      
      printf("Creating structures...\n");
      Adjacency_List adj_list(n, matrix);
      Adjacency_Matrix adj_mat(n, matrix);
      Edge_List e_list(n, matrix);
      Graph_Matrix gmat(n, matrix);
      printf("Done!\n");

      printf("Sorting...\nadj_list\n");
      timespec begin, end;
      
      clock_gettime(CLOCK_REALTIME, &begin);
      adj_list.toposort();
      clock_gettime(CLOCK_REALTIME, &end);
      results[0] += timespec_to_miliseconds(&begin, &end);

      printf("adj_mat\n");
      clock_gettime(CLOCK_REALTIME, &begin);
      adj_mat.toposort();
      clock_gettime(CLOCK_REALTIME, &end);
      results[1] += timespec_to_miliseconds(&begin, &end);

      printf("edge_list\n");
      clock_gettime(CLOCK_REALTIME, &begin);
      e_list.toposort();
      clock_gettime(CLOCK_REALTIME, &end);
      results[2] += timespec_to_miliseconds(&begin, &end);

      printf("graph_mat\n");
      clock_gettime(CLOCK_REALTIME, &begin);
      gmat.toposort();
      clock_gettime(CLOCK_REALTIME, &end);
      results[3] += timespec_to_miliseconds(&begin, &end);

      printf("be free!\n\n\n");
      dag_gen_free(matrix, n);
    }

    for (int i = 0; i < 4; i++) {
      results[0]/=TESTS;
    }
    
    output << " " << results[0] << " " << results[1] << " " << results[2] << " " << results[3] << std::endl;
  }
  output.close();
}
