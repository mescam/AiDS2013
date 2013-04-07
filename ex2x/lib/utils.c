#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int* generate_unique_array(int size) {
  int* arr = (int*)calloc(size, sizeof(int));

  for(int i = 1; i <= size; i++)
    arr[i-1] = 2*i;

  for(int i = size - 1; i >= 1; i--) {
    int to_shuffle = rand() % i + 1;

    int temp = arr[i];
    arr[i] = arr[to_shuffle];
    arr[to_shuffle] = temp;
  }
  
  return arr;
}

void print_array(int *arr, int size) {
  for(int i = 0; i < size; i++)
    printf("%d ", arr[i]);
}
