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
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>

// QS mode flags
#define QS_RIGHT 1
#define QS_RANDOM 2

// definition of stack element
typedef struct Element {
  int l;
  int r;
  struct Element *prev;
} Element;

typedef void(*sortingFunc)(int *t, int n);

// stack functions
void pushToStack(Element **top, int l, int r) {
  Element *el;

  el = (Element*)malloc(sizeof(Element));
  el->l = l;
  el->r = r;
  el->prev = *top;
  *top = el;
}

int* popFromStack(Element **top) {
  int data[2];

  if(*top != NULL) {
    data[0] = (*top)->l;
    data[1] = (*top)->r;

    Element *temp = *top;
    *top = (*top)->prev;
    free(temp);

    return data;
  }
}

void insertionSort(int *t, int n) {
  for(int i = 1; i<n; ++i) {
    int v = t[i];
    int j;

    for(j = i-1; j>=0 && t[j]>v; --j) {
      t[j+1] = t[j];
    }

    t[j+1] = v;
  }
}

void shellSort(int *t, int n) {
  //gap calculation (Prof. Donald Knuth's algorithm)
  int h = 1;
  while(h<n) h = 3*h+1;
  h/=9;
  if(!h) ++h;

  //sorting
  while(h) {
    for(int i = n-h-1; i>=0; --i) {
      int v = t[i];
      int j = i+h;
      while(j<n && v>t[j]) {
        t[j-h] = t[j];
        j += h;
      }
      t[j-h] = v;
    }
    h /= 3;
  }
}

void selectionSort(int *t, int n) {
  int m, tmp;
  for(int i = 0; i<n; ++i) {
    m = i;
    for(int j = i+1; j<n; ++j)
      if(t[j]<t[m])
        m = j;
    tmp = t[i];
    t[i] = t[m];
    t[m] = tmp;
  }
}

void heapSort(int *t, int n) {
  int tmp, p=n/2, i, c;
  while(1) {
    if(p>0) {
      tmp = t[--p];
    } else {
      n--;
      if(!n) return;
      tmp = t[n];
      t[n] = t[0];
    }

    i = p;
    c = i*2+1;

    while(c<n) {
      if(c+1<n && t[c+1]>t[c]) c++; //C++!

      if(t[c]>tmp) {
        t[i] = t[c];
        i = c;
        c = i*2+1;
      } else {
        break;
      }
    }

    t[i] = tmp;
  }
}

void quickSortRecursive(int *t, int l, int r, int mode) {
  int i, j, x;
	
  if(mode == 2)
    x = t[rand() % (r - l) + l + 1];
  else
    x = t[r];
  
  i = l;
  j = r;

  do {
    while(t[i] < x)
      ++i;

    while(t[j] > x)
      --j;

    if(i <= j) {
      int temp = t[i];
      t[i] = t[j];
      t[j] = temp;
      ++i;
      --j;
    }
  }
  while(i < j);
      
  if(l < j)
    quickSortRecursive(t, l, j, mode);
  if(r > i)
    quickSortRecursive(t, i, r, mode);
}

void showArrayOnOutput(int *t, int n) {
  for(int i = 0; i<n; ++i) {
    std::cout << t[i] << " ";
  }
  std::cout << std::endl;
}

int* getDataArray(int n, char z) {
  srand(time(NULL));
  int *t = new int[n];
  for(int i = 0; i<n; i++) {
    switch(z) {

      case 1: //random
        t[i] = rand()%2000;
        break;

      case 2: //ascending
        if(i==0) {
          t[i] = rand()%100;
        } else {
          t[i] = t[i-1]+rand()%100;
        }
        break;

      case 3: //descending
        if(i==0) {
          t[i] = rand()%100;
        } else {
          t[i] = t[i-1]-rand()%100;
        }
        break;

      case 4: //constant
        if(i==0) {
          t[i] = rand()%100;
        } else {
          t[i] = t[i-1];
        }
        break;

      case 5: //V-shaped
        if(i==0) {
          t[i] = rand()%100;
        } else if(i<n/2) {
          t[i] = t[i-1]-rand()%100;
        } else {
          t[i] = t[i-1]+rand()%100;
        }
        break;
    }

  }
  return t;
}

void basicAlgorithmsTest1(sortingFunc f[4]) {

  //I don't think that testing each algorithm with the same range of data is a good idea, so now we have a separated array.
  int n[4][10] = {
    {500, 1000, 2500, 5000, 10000, 20000, 50000, 75000, 100000, 150000},
    {500, 1000, 2500, 5000, 10000, 20000, 50000, 75000, 100000, 150000},
    {500, 1000, 2500, 5000, 10000, 20000, 50000, 75000, 100000, 150000},
    {500, 1000, 2500, 5000, 10000, 20000, 50000, 75000, 100000, 150000},
  };
  int sets[5] = {1,2,3,4,5}; //it's not very helpful, but let's pretend it's important! :D


  for (int i = 0; i < sizeof(f)/sizeof(sortingFunc); i++) { //for each algorithm (as in the first required test)
    std::ostringstream fileName;
    fileName << "results/alg" << i << ".txt";
    std::ofstream output(fileName.str().c_str());

    for (int j = 0; j < sizeof(n[i])/sizeof(int); j++) { //for each n
      output << n[i][j];

      for (int k = 0; k < sizeof(sets)/sizeof(int); k++) { //and for each data set type (it's getting boring :D)

        for (int l = 0; l < 3; l++) { //test it 3 times so the results will be more accurate
          int *t = getDataArray(n[i][j], k+1); //I know about possible data loss
          printf("Testing func %d with n=%d, data set %d, test #%d...\n",i, n[i][j], k+1, l);
          timespec begin, end;
          double timeSpent;

          //starting test!
          clock_gettime(CLOCK_REALTIME, &begin);
          f[i](t, n[i][j]);
          clock_gettime(CLOCK_REALTIME, &end);

          timeSpent = (double) (end.tv_sec - begin.tv_sec)+1.e-9*(end.tv_nsec - begin.tv_nsec);
          timeSpent *= 1000;
          bool sorted=true;

          for (int m = 1; m < n[i][j]; m++) {
            if(t[m-1]>t[m]) sorted=false;
          }

          if(!sorted) {
            printf("\n\n\nERROR! ARRAY IS NOT SORTED!\n\n\n");
            return;
          }

          output << " " << std::setprecision(6) << timeSpent;
          printf("OK! Sorted in %f\n", timeSpent);
          delete[] t;
          t=NULL;
        }

      }
      output << std::endl;
    }
    output.close();
  }
}


int main(int argv, char **argc) {
  sortingFunc f[4] = {insertionSort, shellSort, selectionSort, heapSort};
  basicAlgorithmsTest1(f);
  return 0;
}
/* vim: set ts=2 sw=2 tw=0 et :*/
