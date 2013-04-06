#include <stdio.h>

typedef struct tree_element {
  int key;
  struct tree_element *left, *right, *parent;
} tree_element;

tree_element* tree_init(int *arr, int size);
tree_element* tree_alloc_el(int key);
tree_element* tree_search(tree_element* root, int key);
tree_element* tree_min(tree_element* root);
tree_element* tree_max(tree_element* root);
void tree_insert(tree_element** root, int key);
void tree_remove(tree_element** root, int key);
void tree_print(tree_element* root);
void tree_free(tree_element* root);
void tree_to_array(tree_element* root, int *arr, int *i);
void tree_to_dot(tree_element* root, FILE *file);
void tree_to_file(tree_element* root, const char *file_name);
