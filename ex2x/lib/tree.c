#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h> // MAX macro defined here
#include "tree.h"

tree_element* tree_init(int *arr, int size) {
  tree_element* root = NULL;
  
  for(int i = 0; i < size; i++)
    tree_insert(&root, arr[i]);

  return root;
}

tree_element* tree_alloc_el(int key) {
  tree_element* el = malloc(sizeof(tree_element));
  el->key = key;
  el->left = el->right = el->parent = NULL;

  return el;  
}

void tree_insert(tree_element** root, int key) {
  tree_element* el = *root;
  tree_element* to_parent = NULL;
  tree_element* to_ins = tree_alloc_el(key);
  
  while(el != NULL) {
    to_parent = el;

    if(key < el->key)
      el = el->left;
    else
      el = el->right;
  }

  to_ins->parent = to_parent;

  if(to_parent == NULL)
    *root = to_ins;
  else if(key < to_parent->key)
    to_parent->left = to_ins;
  else if(key > to_parent->key)
    to_parent->right = to_ins;
}

tree_element* tree_search(tree_element *el, int key) {
  while(el != NULL) {
    if(el->key == key)
      break;
    if(key < el->key)
      el = el->left;
    else
      el = el->right;
  }

  return el;
}

tree_element* tree_min(tree_element* el) {
  while(el->left != NULL)
    el = el->left;

  return el;
}

tree_element* tree_max(tree_element* el) {
  while(el->right != NULL)
    el = el->right;

  return el;
}

tree_element* tree_succ(tree_element* el) {
  if(el->right != NULL)
    return tree_min(el->right);

  tree_element* succ = el->parent;
  while(succ != NULL && el == succ->right) {
    el = succ;
    succ = succ->parent;
  }

  return succ;
}

int tree_height(tree_element *el) {
  if(el == NULL)
    return -1;

  return MAX(tree_height(el->left), tree_height(el->right)) + 1;
}

// do not touch, do not hate, it just works
void tree_remove(tree_element **root, int key, int *success) {
  tree_element *to_del, *temp, *el = tree_search(*root, key);

  if(el == NULL) {
    *success = 0;
    return;
  }
  *success = 1;
  if(el->left == NULL || el->right == NULL)
    to_del = el;
  else
    to_del = tree_succ(el);

  if(to_del->left != NULL)
    temp = to_del->left;
  else
    temp = to_del->right;

  if(temp != NULL)
    temp->parent = to_del->parent;
  
  tree_element *par = to_del->parent;
  if(par == NULL)
    *root = temp;
  else if(to_del == par->left)
    par->left = temp;
  else
    par->right = temp;

  if(to_del != el)
    el->key = to_del->key;

  free(to_del);
}

void tree_print(tree_element* root) {
  if(root == NULL)
    return;

  tree_print(root->left);
  printf("%d ", root->key);
  tree_print(root->right);
}

void tree_free(tree_element* root) {
  if(root == NULL)
    return;
  
  tree_free(root->left);
  tree_free(root->right);
  free(root);
}

void tree_to_array(tree_element* root, int *arr, int *i) {
  if(root == NULL)
    return;

  tree_to_array(root->left, arr, i);
  arr[(*i)++] = root->key;
  tree_to_array(root->right, arr, i);
}

void tree_to_dot(tree_element* root, FILE *file) {
  static int dot = 0;

  if(root->left != NULL) {
    fprintf(file, "%d -> %d;\n", root->key, root->left->key);
    tree_to_dot(root->left, file);
  }
  else {
    fprintf(file, "null%d [shape=point];\n", dot);
    fprintf(file, "%d -> null%d;\n", root->key, dot);
    dot++;
  }

  if(root->right != NULL) {
    fprintf(file, "%d -> %d;\n", root->key, root->right->key);
    tree_to_dot(root->right, file);
  }
  else {
    fprintf(file, "null%d [shape=point];\n", dot);
    fprintf(file, "%d -> null%d;\n", root->key, dot);
    dot++;
  }
}

void tree_to_file(tree_element *root, const char *file_name) {
  FILE *f = fopen(file_name, "w");

  if(!f)
    return;

  fprintf(f, "digraph Tree {\n");
  tree_to_dot(root, f);
  fprintf(f, "}");
  fclose(f);
}
