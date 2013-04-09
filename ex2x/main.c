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
int end_party(void);

int main(int argc, char **argv) {
  /*int *arr = generate_unique_array(30);
  tree_element* root = tree_init(arr, 30);

  tree_to_file(root, "dot/test1.dot");
  printf("Height: %d\n", tree_height(root));
  
  free(arr);
  tree_free(root);*/
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
  while(n <= 0 || n >= INT_MAX) {
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
  
}

void list_party(int size) {
  int *arr = generate_unique_array(size, 1);
  list_element* head = list_init_from_array(size, arr);

  printf("Generated data is: ");
  list_print(head);
  printf("\n\n");
  //will finish it overnight
  list_free(head);
}

void tree_party(int size, int type) {
}

int end_party() {
  printf("You're not supposed to do so. Aborting...\n");
  exit(1);
}

