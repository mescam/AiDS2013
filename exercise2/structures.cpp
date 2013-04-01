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

void initAvlTree(int a[], int size);
int qsortCmp(const void *a, const void *b);

int qsortCmp(const void *a, const void *b) {
  int returnCode;
  
  if(*(int*)a < *(int*)b)
    returnCode = -1;
  else if(*(int*)a > *(int*)b)
    returnCode = 1;
  else if(*(int*)a == *(int*)b)
    returnCode = 0;

  return returnCode;
}

/*
 * All kind of utils
 */
int* generateData(int n);
void printArray(int [], int);

// int* generateData(int n) {
//   int *a = new int[n];
//   int c = 0;
// //  int uniqCounter = 0; //for fun :D
  
//   do {
//     int number = rand() % (8*n);

//     bool isUnique = true;
//     for(int i = 0; i < c; i++)
//       if(a[i] == number) {
//         isUnique = false;
//         //      uniqCounter++;
//         break;
//       }

//     if(isUnique)
//       a[c++] = number;
//   }
//   while(c < n);

// //  std::cout << "Not unique: " << uniqCounter << std::endl;

//   return a;
//}

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

//main stuff
int main() {
  srand(time(NULL));

  /* shit goes here */
  
  return 0;
}

/* vim: set ts=2 sw=2 tw=0 et :*/



