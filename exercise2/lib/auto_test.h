#ifndef AUTO_TEST_H

#define AUTO_TEST_H
#include "list.h"
#include "tree.h"

typedef struct _test_set {
  list_element *list;
  tree_element *bst;
  tree_element *avl;
} test_set;
void auto_test_create(int n, double results[], test_set *set); 
void auto_test_flow();

#endif /* end of include guard: AUTO_TEST_H */

