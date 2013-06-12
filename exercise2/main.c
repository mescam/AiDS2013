#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "lib/tree.h"
#include "lib/tree_avl.h"
#include "lib/utils.h"
#include "lib/auto_test.h"

void start_party(void);
void list_party(int size);
void tree_party(int size, int type);

int main(int argc, char **argv) {
  srand(time(NULL));
  if(argc < 2) return 1;

  if(argv[1][0] == 'a')
  	auto_test_flow();
  else
    start_party();

  return 0;
}

void start_party() {
  printf("----------------------------------------------------\n");
  printf("\tAlgorithms and Data Structures\n\tEx. 2 : Data Structures\n");
  printf("Copyright by Jakub Woźniak, Marcin Zaremba\n");
  printf("----------------------------------------------------\n");
  printf("Welcome to testing interface.\nWhich data structure are you interested in?\n");
  printf("1 - List\n2 - BST\n3 - AVL\n");

  int choice = -1;
  while(choice <= 0 || choice > 3) {
    printf("Your choice: ");
    scanf("%d", &choice);
  }

  printf("\nWhat number of elements?\n");

  int n = -1;
  while(n <= 0) {
    printf("Your choice: ");
    scanf("%d", &n);
  }
  
  switch(choice) {
  case 1:
    list_party(n);
    break;
  case 2:
    tree_party(n, 1);
    break;
  case 3:
    tree_party(n, 2);
    break;
  }

  printf("\nThis is the end. Exiting...\n");  
}

void list_party(int size) {
  int *arr = generate_unique_array(size, 1);
  list_element* head = list_init_from_array(size, arr);

  printf("Generated data is: ");
  print_array(arr, size);
  free(arr);
  printf("\nGenerated list is: ");
  list_print(head);
  printf("\n\n");
  
  int n;

  printf("Element to search: ");
  scanf("%d", &n);

  if(list_search(head, n))
    printf("\nFound\n\n");
  else
    printf("\nNot found\n\n");

  n = -1;

  printf("How many elements to insert?\n");

  while(n <= 0) {
    printf("Your choice: ");
    scanf("%d", &n);
  }

  printf("\nType your numbers (space as a delimiter): ");
  int to_ins;
  for(int i = 0; i < n; i++) {
    scanf("%d", &to_ins);
    list_insert(head, to_ins);
  }

  printf("List after inserting: ");
  list_print(head);
  printf("\n\n");

  printf("How many elements to remove?\n");

  n = -1;
  while(n <= 0) {
    printf("Your choice: ");
    scanf("%d", &n);
  }
  
  printf("\nType your numbers (space as delimiter): ");
  int to_del;
  for(int i = 0; i < n; i++) {
    scanf("%d", &to_del);
    if(list_search(head, to_del)) {
      list_remove(head, to_del);
      printf("%d successfully removed.\n", to_del);
    }
    else
      printf("%d not found.\n", to_del);
  }

  printf("\nList after all operations: ");
  list_print(head);
  
  list_free(head);
}

void tree_party(int size, int type) {
  int *arr = generate_unique_array(size, 2);
  tree_element* root = NULL;

  if(type == 1)
    root = tree_init(arr, size);
  else
    root = tree_avl_init(arr, size, 1);

  tree_to_file(root, "dot/before_op.dot");
  
  printf("Generated data is: ");
  print_array(arr, size);
  free(arr);
  printf("\nGenerated tree (in order) is: ");
  tree_print(root);
  int n;
  printf("\n\nElement to search: ");
  scanf("%d", &n);

  if(tree_search(root, n))
    printf("Found\n\n");
  else
    printf("Not found\n\n");

  printf("How many elements to insert:\n");
  n = -1;
  while(n <= 0) {
    printf("Your choice: ");
    scanf("%d", &n);
  }

  printf("Type your numbers (space as a delimiter): ");
  int to_ins;
  for(int i = 0; i < n; i++) {
    scanf("%d", &to_ins);
    tree_insert(&root, to_ins);
  }

  if(type == 2) {
    printf("Rebuilding the tree...");
    tree_avl_rebuild(&root, size + n);
  }

  int new_size = size + n;

  tree_to_file(root, "dot/after_ins.dot");

  printf("\nTree after inserting: ");
  tree_print(root);
  printf("\n\nHow many elements to remove?\n");
  n = -1;
  while(n <= 0) {
    printf("Your choice: ");
    scanf("%d", &n);
  }

  printf("\nType your numbers (space as a delimiter): ");
  int to_del, nobody_needs_it;
  for(int i = 0; i < n; i++) {
    scanf("%d", &to_del);
    if(tree_search(root, to_del)) {
      tree_remove(&root, to_del, &nobody_needs_it);
      printf("%d successfully removed.\n", to_del);
    }
    else
      printf("%d not found.", to_del);
  }

  if(type == 2) {
    printf("\nRebuilding the tree...");
    tree_avl_rebuild(&root, new_size - n);
  }

  tree_to_file(root, "dot/after_op.dot");

  printf("\nTree after all operations: ");
  tree_print(root);
  printf("\nFreeing tree memory...");
  tree_free(root);
}






