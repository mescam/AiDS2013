#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "list.h"

list_element* list_init_from_array(int n, int* array) {
  list_element *head = list_init();
  int i;
  for (i = 0; i < n; i++) {
    list_insert(head, array[i]);
  }
  return head;
}

list_element* list_alloc_el(int key) {
  list_element* el = malloc(sizeof(list_element));
  el->key = key;
  el->next = NULL;

  return el;
}

list_element* list_init() {
  list_element* head = list_alloc_el(-INT_MAX);
  head->next = list_alloc_el(INT_MAX);

  return head;
}

list_element* list_search(list_element *el, int key) {
  el = el->next;

  while(el->key != INT_MAX) {
    if(el->key == key)
      break;

    el = el->next;
  }  
  
  return (el->key == INT_MAX) ? NULL : el;
}

void list_print(list_element *el) {
  el = el->next;

  while(el->key != INT_MAX) {
    printf("%d ", el->key);
    el = el->next;
  }
}

void list_insert(list_element *el, int key) {
  list_element* to_ins = list_alloc_el(key);

  while(el->next->key < key)    
    el = el->next;

  to_ins->next = el->next;
  el->next = to_ins;
}

void list_remove(list_element *el, int key) {
  el = el->next;

  while(el->key != INT_MAX) {
    if(el->next->key == key) {
      list_element *to_del = el->next;
      el->next = el->next->next;
      free(to_del);
      break;
    }
    el = el->next; //rly Marcin, rly?! 
  }
}

void list_free(list_element* el) {
  while(el != NULL) {
    list_element* to_del = el;
    el = el->next;
    free(to_del);
  }
}
