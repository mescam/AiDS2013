#include <stdlib.h>
#include <time.h>
#include "auto_test.h"
#include "utils.h"
#include "tree_avl.h"
#include "utils.h"

#define TESTS 50
/**
 * TODO:
 * - add tree height array 
 * - add inserting and removing tests
 * - maybe more DRY?
 */

 void auto_test_create(int n, double results[], test_set set[]) {
  //o, hai.
  struct timespec begin, end;
  int *array[TESTS], i; 
  results[0]=results[1]=results[2]=0;

  for (i = 0; i < TESTS; ++i)
  {
    printf("test #%d\n",i);
    array[i] = generate_unique_array(n, 1);
    clock_gettime(CLOCK_REALTIME, &begin);
    set[i].list = list_init_from_array(n/10, array[i]);
    clock_gettime(CLOCK_REALTIME, &end);
    results[0] += timespec_to_miliseconds(&begin, &end);

    clock_gettime(CLOCK_REALTIME, &begin);
    set[i].bst = tree_init(array[i], n);
    clock_gettime(CLOCK_REALTIME, &end);
    results[1] += timespec_to_miliseconds(&begin, &end);

    clock_gettime(CLOCK_REALTIME, &begin);
    set[i].avl = tree_avl_init(array[i], n, 1);
    clock_gettime(CLOCK_REALTIME, &end);
    results[2] += timespec_to_miliseconds(&begin, &end);

    free(array[i]);
  }

  for (i = 0; i < 3; ++i)
    results[i]/=TESTS;


  return;
}

void auto_test_insert(int n, double results[], test_set *set) {
  int to_insert = n/100, *arr, i,j;
  struct timespec begin, end;
  results[0]=results[1]=results[2]=0;

  for (i = 0; i < TESTS; ++i)
  {
    printf("test #%d\n",i);
    arr = generate_unique_array(n, 0);
    //list
    clock_gettime(CLOCK_REALTIME, &begin);
    for (j = 0; j < to_insert/10; j++) {
      list_insert(set[i].list, arr[j]);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    results[0] += timespec_to_miliseconds(&begin, &end);

    //bst
    clock_gettime(CLOCK_REALTIME, &begin);
    for (j = 0; j < to_insert/10; j++) {
      tree_insert(&(set[i].bst), arr[j]);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    results[1] += timespec_to_miliseconds(&begin, &end);

    //avl
    clock_gettime(CLOCK_REALTIME, &begin);
    for (j = 0; j < to_insert; j++) {
      tree_insert(&(set[i].avl), arr[j]);
    }
    tree_avl_rebuild(&(set[i].avl),n+to_insert);
    clock_gettime(CLOCK_REALTIME, &end);
    results[2] = timespec_to_miliseconds(&begin, &end);

    free(arr); /*arr, you are a pirate!*/
  }

  for (i = 0; i < 3; ++i)
    results[i]/=TESTS;

  return;
  
}

void auto_test_remove(int n, double results[], test_set *set) {
  int to_remove = n/100, i, size = n+to_remove, success, j;
  int *array = (int*)malloc(sizeof(int)*to_remove);
  struct timespec begin, end;
  results[0]=results[1]=results[2]=0;
  printf("debug: n=%d; size=%d; results[2]=%f\n",n,size,results[2]);
  for (i = 0; i < to_remove; i++)
    array[i] = rand()%size;

  for (i = 0; i < TESTS; ++i)
  {
    printf("test #%d\n",i);
    //list
    clock_gettime(CLOCK_REALTIME, &begin);
    for (j = 0; j < to_remove/10; j++)
      list_remove(set[i].list, array[j]);
    clock_gettime(CLOCK_REALTIME, &end);
    results[0] += timespec_to_miliseconds(&begin, &end);

  //bst
    clock_gettime(CLOCK_REALTIME, &begin);
    for (j = 0; j < to_remove; j++)
      tree_remove(&(set[i].bst), array[j], &success);
    clock_gettime(CLOCK_REALTIME, &end);
    results[1] += timespec_to_miliseconds(&begin, &end);

  //avl
    int size_cpy = size;
    clock_gettime(CLOCK_REALTIME, &begin);
    for (j = 0; j < to_remove; j++) {
      tree_remove(&(set[i].avl), array[j], &success);
      if(success == 1) size_cpy--;
    }
    tree_avl_rebuild(&(set[i].avl), size_cpy);
    clock_gettime(CLOCK_REALTIME, &end);
    results[2] += timespec_to_miliseconds(&begin, &end);
  }
  
  for (i = 0; i < 3; ++i)
  {
    results[i]/=TESTS;
  }

  free(array);
  return;
}

void auto_test_flow() { 
  FILE *files[4];
  int i;
  int n[11] = {0, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
  double results[3];
  test_set set[TESTS];

  for(i = 0; i < 4; i++) {
    char buffer[10];
    sprintf(buffer, "tests/results_%d.txt",i+1);
    files[i] = fopen(buffer, "w+");
    if(files[i]==NULL) {
      fprintf(stderr, "Error opening test [%d] file", i);
      return;
    }
  }

  for (i = 0; i < 11; i++) {//for each n
    fprintf(stdout, "------------------------\nTESTING FOR N=%d\n", n[i]);
    fprintf(stdout, "Creating structures...\n");
    auto_test_create(n[i], results, set);
    fprintf(files[0], "%d %f %f %f\n", n[i], results[0], results[1], results[2]);
    //fprintf(stdout, "Calculating trees' height...\n");
    //fprintf(files[1], "%d %d %d\n", n[i], tree_height(set[0].bst), tree_height(set[0].avl));
    fprintf(stdout, "Inserting test...\n");
    auto_test_insert(n[i], results, set);
    fprintf(files[2], "%d %f %f %f\n", n[i], results[0], results[1], results[2]);
    fprintf(stdout, "Removing test...\n");
    auto_test_remove(n[i], results, set);
    fprintf(files[3], "%d %f %f %f\n", n[i], results[0], results[1], results[2]);
    fprintf(stdout, "Done!\n------------------------\n\n");
  }

  for (i = 0; i < 4; i++) {
    fclose(files[i]);
  }

  for (i = 0; i < TESTS; ++i)
  {
    list_free(set[i].list);
    tree_free(set[i].bst);
    tree_free(set[i].avl);
  }
  
}



