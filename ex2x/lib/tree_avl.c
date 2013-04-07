#include <stdlib.h>
#include "tree.h"
#include "tree_avl.h"

tree_element* tree_avl_init_rec(int *arr, int left, int right) {
  int part = (left + right) / 2;

  tree_element* el = tree_alloc_el(arr[part]);

  if(left <= (part - 1)) {
    el->left = tree_avl_init_rec(arr, left, part - 1);
    el->left->parent = el;
  }

  if(right >= (part + 1)) {
    el->right = tree_avl_init_rec(arr, part + 1, right);
    el->right->parent = el;
  }

  return el;  
}

tree_element* tree_avl_init(int *arr, int size, int first) {
  if(first == 1) 
    qsort(arr, size, sizeof(int), qsort_cmp);
  return tree_avl_init_rec(arr, 0, size - 1);
}

void tree_avl_rebuild(tree_element **root, const int size) {
  int arr[size], i = 0;

  tree_to_array(*root, arr, &i);
  tree_free(*root);
  *root = tree_avl_init(arr, size, 0);
}

int qsort_cmp(const void *a, const void *b) {
  if(*(int*)a < *(int*)b)
    return -1;
  else if(*(int*)a > *(int*)b)
    return 1;
  else if(*(int*)a == *(int*)b)
    return 0;

  return 0;
}



