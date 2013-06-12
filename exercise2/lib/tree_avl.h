#ifndef TREE_AVL_H

#define TREE_AVL_H
tree_element* tree_avl_init(int *arr, int size, int first);
tree_element* tree_avl_init_rec(int *arr, int left, int right);
void tree_avl_rebuild(tree_element **root, int size);
int qsort_cmp(const void *a, const void *b);


#endif /* end of include guard: TREE_AVL_H */

