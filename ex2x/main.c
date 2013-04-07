#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "lib/tree.h"
#include "lib/tree_avl.h"
#include "lib/utils.h"
#include "lib/auto_test.h"

int main(int argc, char **argv) {
  /*int *arr = generate_unique_array(30);
  tree_element* root = tree_init(arr, 30);

  tree_to_file(root, "dot/test1.dot");
  printf("Height: %d\n", tree_height(root));
  
  free(arr);
  tree_free(root);*/
  auto_test_flow();
}
