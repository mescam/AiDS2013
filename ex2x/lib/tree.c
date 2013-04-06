#include <stdio.h>
#include <stdlib.h>
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

tree_element* tree_min(tree_element *el) {
  while(el->left != NULL)
    el = el->left;

  return el;
}

tree_element* tree_max(tree_element* el) {
  while(el->right != NULL)
    el = el->right;

  return el;
}

// do not touch, do not hate, it just works
void tree_remove(tree_element **root, int key) {
  tree_element *to_del = tree_search(*root, key);

  if(to_del == NULL)
    return;

  tree_element *parent, **parent_side;
  if(to_del->parent != NULL) {
    parent = to_del->parent;
    parent_side = (parent->left == to_del) ? &(parent->left) : &(parent->right);
  }
  else
    parent = NULL;
      
  if(to_del->left == NULL && to_del->right == NULL) {
    if(parent != NULL)
      *parent_side = NULL;
    else
      *root = NULL;
    
    free(to_del);
  }
  else if(to_del->left != NULL && to_del->right != NULL) {
    tree_element *to_replace = tree_max(to_del->left);

    tree_element **very_parent_side;

    very_parent_side = (to_replace->parent->left == to_replace) ? &(to_replace->parent->left) : &(to_replace->parent->right);
    
    to_del->key = to_replace->key;

    *very_parent_side = NULL;

    free(to_replace);
  }
  else {
    tree_element *to_replace = (to_del->left != NULL) ? to_del->left :to_del->right;

    *parent_side = to_replace;
    to_replace->parent = parent;
    
    free(to_del);
  }
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
