typedef struct list_element {
  int key;
  struct list_element* next;
} list_element;

list_element* list_init();
list_element* list_alloc_el(int key);
list_element* list_search(list_element* head, int key);
void list_insert(list_element* head, int key);
void list_remove(list_element* head, int key);
void list_print(list_element* head);
void list_free(list_element* head);
