#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/tree.h"
#include "lib/tree_avl.h"
#include "lib/utils.h"

int main(int argc, char **argv) {
  srand(time(NULL));

  int *arr = generate_unique_array(50);

  tree_element *root = tree_avl_init(arr,50);
  tree_to_file(root, "dot/test1.dot");  
  tree_remove(&root, 1);
  tree_remove(&root, 2);
  tree_avl_rebuild(&root, 48);
  tree_to_file(root, "dot/test2.dot");  

  free(arr);
  tree_free(root);
}
