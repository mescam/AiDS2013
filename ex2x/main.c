#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/tree.h"
#include "lib/tree_avl.h"

int main(void) {
  srand(time(NULL));

  int arr[10];
  for(int i = 0; i < 10; i++)
    arr[i] = rand() % 500;

  tree_element *root = tree_avl_init(arr,10);
  tree_print(root);
  tree_to_file(root, "dot/test1.dot");
  int rem;
  scanf("%d",&rem);
  printf("\n\n");
  tree_remove(&root, rem);
  tree_to_file(root, "dot/test2.dot");
  tree_avl_rebuild(&root, 9);
  tree_to_file(root, "dot/test3.dot");

  printf("\n\n");

  tree_free(root);
}
