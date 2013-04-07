#include <stdlib.h>
#include <time.h>
#include "auto_test.h"
#include "utils.h"
#include "tree_avl.h"
#include "utils.h"

/**
 * TODO:
 * - add tree height array 
 * - add inserting and removing tests
 * - maybe more DRY?
 */

void auto_test_create(int n, double results[], test_set *set) {
  //o, hai.
  struct timespec begin, end;
  int *array = generate_unique_array(n, 1); //only even numbers.

  fprintf(stdout, "list "); fflush(stdout);
  clock_gettime(CLOCK_REALTIME, &begin);
  set->list = list_init_from_array(n, array);
  clock_gettime(CLOCK_REALTIME, &end);
  results[0] = timespec_to_miliseconds(&begin, &end);

  fprintf(stdout, "bst "); fflush(stdout);
  clock_gettime(CLOCK_REALTIME, &begin);
  set->bst = tree_init(array, n);
  clock_gettime(CLOCK_REALTIME, &end);
  results[1] = timespec_to_miliseconds(&begin, &end);

  fprintf(stdout, "avl\n");
  clock_gettime(CLOCK_REALTIME, &begin);
  set->avl = tree_avl_init(array, n);
  clock_gettime(CLOCK_REALTIME, &end);
  results[2] = timespec_to_miliseconds(&begin, &end);

  free(array);
  return;
}

void auto_test_insert(int n, double results[], test_set *set) {
  int to_insert = n/100, *arr = generate_unique_array(to_insert, 0), i;
  struct timespec begin, end;

  //list
  fprintf(stdout, "list "); fflush(stdout);
  clock_gettime(CLOCK_REALTIME, &begin);
  for (i = 0; i < to_insert; i++) {
    list_insert(set->list, arr[i]);
  }
  clock_gettime(CLOCK_REALTIME, &end);
  results[0] = timespec_to_miliseconds(&begin, &end);

  //bst
  fprintf(stdout, "bst "); fflush(stdout);
  clock_gettime(CLOCK_REALTIME, &begin);
  for (i = 0; i < to_insert; i++) {
    tree_insert(&(set->bst), arr[i]);
  }
  clock_gettime(CLOCK_REALTIME, &end);
  results[1] = timespec_to_miliseconds(&begin, &end);

  //avl
  fprintf(stdout, "avl\n");
  clock_gettime(CLOCK_REALTIME, &begin);
  for (i = 0; i < to_insert; i++) {
    tree_insert(&(set->avl), arr[i]);
  }
  tree_avl_rebuild(&(set->avl),n+to_insert);
  clock_gettime(CLOCK_REALTIME, &end);
  results[2] = timespec_to_miliseconds(&begin, &end);

  free(arr); /*arr, you are a pirate!*/
}

void auto_test_remove(int n, double results[], test_set *set) {
  int to_remove = n/100, i, size = n+to_remove, success;
  int *array = (int*)malloc(sizeof(int)*to_remove);
  struct timespec begin, end;

  for (i = 0; i < to_remove; i++)
    array[i] = rand()%size;

  //list
  fprintf(stdout, "list "); fflush(stdout);
  clock_gettime(CLOCK_REALTIME, &begin);
  for (i = 0; i < to_remove; i++)
    list_remove(set->list, array[i]);
  clock_gettime(CLOCK_REALTIME, &end);
  results[0] = timespec_to_miliseconds(&begin, &end);

  //bst
  fprintf(stdout, "bst "); fflush(stdout);
  clock_gettime(CLOCK_REALTIME, &begin);
  for (i = 0; i < to_remove; i++)
    tree_remove(&(set->avl), array[i], &success);
  clock_gettime(CLOCK_REALTIME, &end);
  results[1] = timespec_to_miliseconds(&begin, &end);

  //avl
  fprintf(stdout, "avl \n");
  clock_gettime(CLOCK_REALTIME, &begin);
  for (i = 0; i < to_remove; i++) {
    tree_remove(&(set->avl), array[i], &success);
    if(success == 1) size--;
  }
  tree_avl_rebuild(&(set->avl), size);
  clock_gettime(CLOCK_REALTIME, &end);
  results[2] = timespec_to_miliseconds(&begin, &end);

  free(array);
  return;
}

void auto_test_flow() { 
  FILE *files[4];
  int i;
  int n[10] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000};
  double results[10][3];
  test_set set;

  for(i = 0; i < 4; i++) {
    char buffer[10];
    sprintf(buffer, "tests/results_%d.txt",i+1);
    files[i] = fopen(buffer, "w+");
    if(files[i]==NULL) {
      fprintf(stderr, "Error opening test [%d] file", i);
      return;
    }
  }

  for (i = 0; i < 10; i++) {//for each n
    fprintf(stdout, "------------------------\nTESTING FOR N=%d\n", n[i]);
    fprintf(stdout, "Creating structures...\n");
    auto_test_create(n[i], results[i], &set);
    fprintf(files[0], "%d %f %f %f\n", n[i], results[i][0], results[i][1], results[i][2]);
    fprintf(stdout, "Calculating trees' height...\n");
    fprintf(files[1], "%d %d %d\n", n[i], tree_height(set.bst), tree_height(set.avl));
    fprintf(stdout, "Inserting test...\n");
    auto_test_insert(n[i], results[i], &set);
    fprintf(files[2], "%d %f %f %f\n", n[i], results[i][0], results[i][1], results[i][2]);
    fprintf(stdout, "Removing test...\n");
    auto_test_remove(n[i], results[i], &set);
    fprintf(files[3], "%d %f %f %f\n", n[i], results[i][0], results[i][1], results[i][2]);
    fprintf(stdout, "Done!\n------------------------\n\n");
  }

  for (i = 0; i < 4; i++) {
    fclose(files[i]);
  }

  list_free(set.list);
  tree_free(set.bst);
  tree_free(set.avl);
}



