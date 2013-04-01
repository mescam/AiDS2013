/*-*- tab-width:2; indent-tabs-mode:nil;c-basic-offset:2; -*-*/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Copyright (C) Jakub Woźniak, Marcin Zaremba, 2013
 */

#include <iostream>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>

/*
 * Dynamic list implementation
 *
 */

struct ListElement {
  int key;
  ListElement *next;
};

typedef ListElement* PListElement;

PListElement initListElement(int);
void insertListElement(PListElement &, int);
void destroyListElement(PListElement &, int);
PListElement initList();
PListElement searchList(PListElement &, int);
void printList(PListElement &);
void freeList(PListElement &);  

PListElement initList() {
  /*
    why is that thing?
    there're our guards, inserting with 'em is just heaven,
    without - hell. (so much ifs needed then)
  */
  PListElement el = initListElement(-INT_MAX);
  el->next = initListElement(INT_MAX);

  return el;
}

PListElement initListElement(int key) {
  PListElement el = new ListElement; 
  el->key = key;
  el->next = NULL;

  return el;
}

void destroyListElement(PListElement &head, int key) {
  PListElement el = head;

  while(el->key != INT_MAX) {
    if(el->next->key == key) {
      PListElement toDel = el->next;
      el->next = el->next->next;
      delete toDel;
      break;
    }

    el = el->next;
  }
}

void freeList(PListElement &head) {
  PListElement el, toDel;

  el = head;

  while(el != NULL) {
    toDel = el;
    el = el->next;
    delete toDel;
  }
}

void insertListElement(PListElement &head, int key) {
  PListElement toIns = initListElement(key);
  PListElement el;

  for(el = head; key > el->next->key; el = el->next);
  toIns->next = el->next;
  el->next = toIns;
}

PListElement searchList(PListElement &head, int key) {
  PListElement el;
 
  for(el = head; el->key != INT_MAX; el = el->next)
    if(el->key == key)
      break;
 
  return el->key == INT_MAX ? NULL : el;
}

void printList(PListElement &head) {
  PListElement el = head->next;

  while(el->key != INT_MAX) {
    std::cout << el->key << " ";
    el = el->next;
  }
}

/*
 * BST implementation
 *
 */

struct BstElement {
  int key;
  BstElement *left;
  BstElement *right;
  BstElement *parent;
};

typedef BstElement* PBstElement;

PBstElement initBstTree(int [], int);
PBstElement initBstElement(int);
void insertBstElement(PBstElement &, int);
void destroyBstElement(PBstElement &, int);
PBstElement searchBstTree(PBstElement &, int);
void printBstTree(PBstElement);
void freeBstTree(PBstElement);

PBstElement initBstTree(int a[], int size) {
  PBstElement root = NULL;
  
  for(int i = 0; i < size; i++)
    insertBstElement(root, a[i]);

  return root;
}

PBstElement initBstElement(int key) {
  PBstElement el = new BstElement;
  el->key = key;
  el->right = NULL;
  el->left = NULL;
  el->parent = NULL;

  return el;
}

void insertBstElement(PBstElement &root, int key) {
  PBstElement toParent = NULL;
  PBstElement el = root;
  PBstElement toIns = initBstElement(key);

  while(el != NULL) {
    toParent = el;

    if(key < el->key)
      el = el->left;
    else
      el = el->right;
  }

  toIns->parent = toParent;

  if(toParent == NULL)
    root = toIns;
  else if(key < toParent->key)
    toParent->left = toIns;
  else if(key > toParent->key)
    toParent->right = toIns;
}

void destroyBstElement(PBstElement &root, int key) {
  PBstElement el = searchBstTree(root, key);

  if(el->left && el->right) {
    std::cout << "both children";
  }
  else if(el->left) {
    std::cout << "one child";
  }
  else {
    
  }
}

void freeBstTree(PBstElement el) {
  if(el != NULL) {
    freeBstTree(el->left);
    freeBstTree(el->right);
    delete el;
  }
}

PBstElement searchBstTree(PBstElement &root, int key) {
  PBstElement el = root;

  while(el != NULL && el->key != key) {
    if(key < el->key)
      el = el->left;
    else
      el = el->right;    
  }

  return el;
}

void printBstTree(PBstElement el) {
  if(el != NULL) {
    printBstTree(el->left);
    std::cout << el->key << " ";
    printBstTree(el->right);
  }
}

/*
 * AVL implementation
 *
 */
struct AVLNode {
  int value, ratio;
  AVLNode *parent, *left, *right;
};

AVLNode *initAvlTree(int a[], int size);
int qsortCmp(const void *a, const void *b);
//AVLNode *initAvlTreeBounded(int a[], int size, int left, int right, AVLNode *root);


AVLNode *initAvlTreeBounded(int a[], int size, int left, int right) {
  int key = (left+right)/2;

  //printf("Wywolanie l=%d r=%d k=%d\n",left,right,key);
  
  AVLNode *root = new AVLNode;
  root->left = nullptr; 
  root->right = nullptr;
  root->parent = nullptr;
  root->value = a[key];

  if(left<=(key-1)) {
    root->left = initAvlTreeBounded(a, size, left, key-1);
    root->left->parent = root;
  }
  if((key+1)<=right) {
    root->right = initAvlTreeBounded(a, size, key+1, right);
    root->right->parent = root;
  }

  return root;
}

AVLNode *initAvlTree(int a[], int size) {
  //AVLNode *root = nullptr;
  std::qsort(a, size, sizeof(int), qsortCmp);

  return initAvlTreeBounded(a, size, 0, size-1);
}

AVLNode *searchAvlTree(AVLNode *root, int value) {
  AVLNode *node = root;

  while(node != nullptr && node->value != value) {
    if(value < node->value)
      node = node->left;
    else
      node = node->right;
  }
  //sorry, Marcin :D
  return node;
}

AVLNode *insertAvlTree(AVLNode *root, int value) {
  AVLNode *node = new AVLNode;
  node->value = value;
  node->left = node->right = node->parent = nullptr;

  while((root->left != nullptr && root->value > node->value ) || (root->right != nullptr && root->value < node->value)) {
    if(root->value > node->value) root=root->left;
    else root=root->right;
  } //they see me codin', they hatin'

  if(node->value > root->value) root->right = node;
  else root->left = node;

  node->parent = root;
  return node;
}

void deleteAvlTree(AVLNode *root) {
  //post order - left right key
  if(root->left != nullptr) deleteAvlTree(root->left);
  if(root->right != nullptr) deleteAvlTree(root->right);
  delete root;
}

AVLNode *findMaxAvlTree(AVLNode *root) {
  while(root->right != nullptr) root=root->right;
  return root;
}


AVLNode *removeNodeAvlTree(AVLNode *root, int value) {
  
  AVLNode *node = searchAvlTree(root, value), *parent, **parentLink;
  if(node==nullptr) return root;
  //why would I do that? :<
  parent = node->parent;
  if(parent != nullptr) parentLink = (parent->left==root)?&(parent->left):&(parent->right);
  else parentLink=nullptr;

  if(node->left == nullptr && node->right == nullptr) { //leaf!
    if(parent != nullptr) *parentLink=nullptr;
    else root=nullptr;
    delete node;
  }
  else if(node->left != nullptr && node->right != nullptr) { //both children
    AVLNode *newPope = findMaxAvlTree(node->left);
    node->value = newPope->value;
    newPope->parent->right = nullptr;
    delete newPope;
  }
  else if(node->left != nullptr || node->right != nullptr) { //one child ()
    AVLNode *child = (node->left!=nullptr)?node->left:node->right;
    child->parent = node->parent;
    
    if(parent != nullptr) *parentLink=child;
    else root=nullptr;
    
    delete node;
  }
  return root;
}

void inOrderAvlTree(AVLNode *node, int *arr, int *i) {
  if(node->left != nullptr) inOrderAvlTree(node->left, arr, i);
  arr[(*i)++] = node->value;
  if(node->right != nullptr) inOrderAvlTree(node->right, arr, i);
}

AVLNode *InOutAfterpartyAvlTree(AVLNode *root, int num) {
  int *array = new int[num], i = 0;
  //in order - left key right
  inOrderAvlTree(root, array, &i);
  deleteAvlTree(root);
  return initAvlTree(array, num);
}

int qsortCmp(const void *a, const void *b) {
  
  if(*(int*)a < *(int*)b)
    return -1;
  else if(*(int*)a > *(int*)b)
    return 1;
  else if(*(int*)a == *(int*)b)
    return 0;

  return 0;
}

/*
 * All kind of utils
 */
int* generateData(int n);
void printArray(int [], int);

void printAvlTree(AVLNode *node){
  std::cout << node->value << " ";
  if(node->left != nullptr) printAvlTree(node->left);
  if(node->right != nullptr) printAvlTree(node->right);
}

int* generateData(int n) {
  const int howMuch = 5 * n;
  
  /* dynamically allocated because
   * howMuch circa about 4M kills
   * static C++ binding
   */
  int *k = new int[howMuch];
  int *a = new int[n];

  for(int i = 0; i < howMuch; i++)
    k[i] = i + 1;

  for(int i = howMuch * 10; i > 0; i--) {
    int indexOne = rand() % howMuch;
    int indexTwo = rand() % howMuch;

    std::swap(k[indexOne], k[indexTwo]);
  }

  for(int i = 0; i < n; i++)
    a[i] = k[i];

  delete[] k;
  
  return a;
}

void printArray(int a[], int size) {
  for(int i = 0; i < size; i++)
    std::cout << a[i] << " ";
}

void dotPrintPart(AVLNode *node, std::ofstream *out){
  static int dot = 0;
  if(node->left != nullptr){
    *out << node->value << " -> " << node->left->value << ";"  << std::endl;
    dotPrintPart(node->left, out);
  }else{
    *out << "null"<<dot<<" [shape=point];" <<std::endl;
    *out << node->value << " -> null"<<dot << ";"  << std::endl;
    dot++;
  }
  if(node->right != nullptr){
    *out << node->value << " -> " << node->right->value << ";" <<std::endl;
    dotPrintPart(node->right, out);
  }else{
    *out << "null"<<dot<<" [shape=point];" <<std::endl;
    *out << node->value << " -> null"<< dot << ";"  << std::endl;
    dot++;
  }
}

void dotPrintTree(AVLNode *root) {
  std::ofstream out("avl.dot");
  out << "digraph AVL {" << std::endl;
  dotPrintPart(root, &out);
  out << "}";
  out.close();
}

//main stuff
int main() {
  srand(time(NULL));

  /* shit goes here */
  int* arr = generateData(10);
  AVLNode* r = initAvlTree(arr, 10);
  printAvlTree(r); 
  std::cout << std::endl << "Dodaj wartosc: ";
  int a,b;
  std::cin >> a;
  insertAvlTree(r, a);
  InOutAfterpartyAvlTree(r, 11);
  std::cout << "Usun wartosc: ";
  std::cin >> b;
  removeNodeAvlTree(r, b);
  InOutAfterpartyAvlTree(r, 10);
  dotPrintTree(r); //$ dot -Tpng -Oavl.png avl.dot
  deleteAvlTree(r);
  delete[] arr;
  
  return 0;
}

/* vim: set ts=2 sw=2 tw=0 et :*/



