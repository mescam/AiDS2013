#include <stdlib.h>
#include <time.h>
#include "auto_test.h"
#include "utils.h"
#include "tree_avl.h"
#include "utils.h"


void auto_test_create(int n, double results[], test_set *set) {
  //o, hai.
  struct timespec begin, end;
  int *array = generate_unique_array(n); //only even numbers.

  clock_gettime(CLOCK_REALTIME, &begin);
  set->list = list_init_from_array(n, array);
  clock_gettime(CLOCK_REALTIME, &end);
  results[0] = (double) (end.tv_sec - begin.tv_sec)+1.e-9*(end.tv_nsec - begin.tv_nsec);

  clock_gettime(CLOCK_REALTIME, &begin);
  set->bst = tree_init(array, n);
  clock_gettime(CLOCK_REALTIME, &end);
  results[1] = (double) (end.tv_sec - begin.tv_sec)+1.e-9*(end.tv_nsec - begin.tv_nsec);

  clock_gettime(CLOCK_REALTIME, &begin);
  set->avl = tree_avl_init(array, n);
  clock_gettime(CLOCK_REALTIME, &end);
  results[2] = (double) (end.tv_sec - begin.tv_sec)+1.e-9*(end.tv_nsec - begin.tv_nsec);
  free(array);
  return;
}

void auto_test_flow() { 
  FILE *files[3];
  int i;
  int n[10] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000};
  double results[10][3];
  test_set set;

  for(i = 0; i < 3; i++) {
    char buffer[10];
    sprintf(buffer, "tests/results_%d.txt",i+1);
    files[i] = fopen(buffer, "w+");
    if(files[i]==NULL) {
      fprintf(stderr, "Error opening test [%d] file", i);
      return;
    }
  }

  for (i = 0; i < 10; i++) {//for each n
    auto_test_create(n[i], results[i], &set);
    fprintf(files[0],"%d %f %f %f\n",n[i], results[i][0], results[i][1], results[i][2]); 
  }

  for (i = 0; i < 3; i++) {
    fclose(files[i]);
  }
}



