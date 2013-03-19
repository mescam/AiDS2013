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
typedef void(*quickFunc)(int *t, int l, int r, int mode);
// stack functions
void pushToStack(Element **top, int l, int r) {
  Element *el;

  el = (Element*)malloc(sizeof(Element));
  el->l = l;
  el->r = r;
  el->prev = *top;
  *top = el;
}

void popFromStack(Element **top, int *d) {
  int data[2];

  if(*top != NULL) {
    data[0] = (*top)->l;
    data[1] = (*top)->r;

    Element *temp = *top;
    *top = (*top)->prev;
    free(temp);

    memcpy(d, data, sizeof(data));
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

void shellSort(int *t, int size)
{
  int h;

  for(h = 1; h < size; h = 3 * h + 1);
  h /= 9;
  if(!h)
    h = 1;

  while(h > 0)
  {   
    for(int i = h; i < size; i++)
    {
      int key = t[i];
      int j;

      for(j = i - h; j >= 0 && t[j] > key; j -= h)
        t[j + h] = t[j];
      t[j + h] = key;
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


void heapify(int *t, int n, int a) {
  int left = (2*(a+1))-1;
  int right = 2*(a+1);

  int largest=a;

  if(left<n && t[left]>t[largest]) largest=left;
  if(right<n && t[right]>t[largest]) largest=right;

  if(largest!=a) {
    std::swap(t[largest], t[a]);
    heapify(t, n, largest);
  }
}

void heapSort(int *t, int n) {
  //building the heap
  for (int i = (n/2)-1; i >= 0; i--)
    heapify(t, n, i);

  //so now we can sort it
  for (int i = n-1; i>0; i--) {
    std::swap(t[0],t[i]);
    heapify(t, --n, 0);
  }
}

void quickSortPartition(int *t, int l, int r, int mode, int *d) {
  int i, j, x;
  int data[2];

  if(mode == 2)
    x = t[rand() % (r - l) + l + 1];
  else
    x = t[l];

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

  data[0] = i;
  data[1] = j;

  memcpy(d, data, sizeof(data));
}

void quickSortRecursive(int *t, int l, int r, int mode) {
  int d[2];

  quickSortPartition(t, l, r, mode, d);

  if(l < d[1])
    quickSortRecursive(t, l, d[1], mode);
  if(r > d[0])
    quickSortRecursive(t, d[0], r, mode);
}

void quickSortIterative(int *t, int l, int r, int mode) {
  Element *top = NULL;
  int el_data[2], part_data[2];

  pushToStack(&top, l, r);

  while(top != NULL) {
    popFromStack(&top, el_data);

    quickSortPartition(t, el_data[0], el_data[1], mode, part_data);

    if(el_data[0] < part_data[1])
      pushToStack(&top, el_data[0], part_data[1]);
    if(el_data[1] > part_data[0])
      pushToStack(&top, part_data[0], el_data[1]);
  }  
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

void basicAlgorithmsTest(sortingFunc f[4]){
  int n[3][10] = {
    {1000, 5000, 10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000}, //linear
    {1000, 5000, 10000, 15000, 20000, 50000, 75000, 100000, 150000, 200000}, //nlogn or n^(3/2)
    {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000} //n^2
  };

  int *usingN[4][5] = {
    //random ascending descending constant v-shaped
    {n[2], n[0], n[2], n[0], n[2]}, //insertion
    {n[1], n[1], n[1], n[1], n[1]},//shell sort
    {n[2], n[2], n[2], n[2], n[2]}, //selection
    {n[1], n[1], n[1], n[1], n[1]}
  };
  std::ofstream output("results/results.txt");

  for (int i = 0; i < 4; i++) { //sorting func
    output << "Algorithm #" << i+1 << std::endl;
    for (int j = 1; j < 6; j++) {
      output << "Testing data #" << j << std::endl;

      for (int k = 0; k < 10; k++) {
        printf("Testing algorithm #%d, data set #%d, n=%d\n",i,j,usingN[i][j-1][k]);
        int *t = getDataArray(usingN[i][j-1][k], j);

        timespec begin, end;
        double timeSpent;

        //starting test!
        clock_gettime(CLOCK_REALTIME, &begin);
        f[i](t, usingN[i][j-1][k]);
        clock_gettime(CLOCK_REALTIME, &end);

        timeSpent = (double) (end.tv_sec - begin.tv_sec)+1.e-9*(end.tv_nsec - begin.tv_nsec);
        timeSpent *= 1000;
        bool sorted=true;

        for (int m = 1; m < usingN[i][j-1][k]; m++) {
          if(t[m-1]>t[m]) sorted=false;
        }

        if(!sorted) {
          printf("\n\n\nERROR! ARRAY IS NOT SORTED!\n\n\n");
          return;
        }

        output << usingN[i][j-1][k] << " " << std::setprecision(6) << timeSpent << std::endl;

        delete[] t;
      }

    }
  }

  output.close();

}

void quickSortTest(quickFunc q[2]){
  int data[4] = {3,4,1,5};
  //int n[10 ] =  {1000, 2000, 5000, 10000, 15000, 20000, 35000, 50000, 75000, 100000};
  int dd[3][10] = {
    {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000},
    {1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 750000, 1000000},
    {1000, 2000, 4000, 5000, 7000, 10000, 12000, 14000, 16000, 20000}
  };

  int *ddd[4][2][2]{
    {{dd[0],dd[1]},{dd[0],dd[1]}},//descending
      {{dd[1],dd[1]},{dd[1],dd[1]}}, //constant
      {{dd[1],dd[1]},{dd[1],dd[1]}}, //random
      {{dd[1],dd[1]},{dd[1],dd[1]}} //v-shaped
  };//trolololololololo!

  std::ofstream output("results/quick.txt");
  for (int i = 0; i < 4; i++) { //data type
    output << "Data type " << i << std::endl;
    for (int j = 0; j < 2; j++) { //function
      output << "Function #" << j << std::endl;
      for (int k = 0; k < 2; k++) { //key
        output << "Key " << k << std::endl;

        for (int l = 0; l < 10; l++) {

          double timeSpent[5];
          int **n = ddd[i][j];

          for (int m = 0; m < 5; m++) {

            printf("Testing algorithm %d for data type %d with key %d, n=%d\n", j, i, k, n[k][l]);
            int *t = getDataArray(n[k][l], data[i]);
            timespec begin, end;

            clock_gettime(CLOCK_REALTIME, &begin);
            q[j](t, 0, n[k][l]-1, k+1);
            clock_gettime(CLOCK_REALTIME, &end);

            timeSpent[m] = (double) (end.tv_sec - begin.tv_sec)+1.e-9*(end.tv_nsec - begin.tv_nsec);
            timeSpent[m] *= 1000;
            bool sorted=true;

            for (int w = 1; w < n[k][l]; w++) {
              if(t[w-1]>t[w]) sorted=false;
            }

            if(!sorted) {
              printf("\n\n\nERROR! ARRAY IS NOT SORTED!\n\n\n");
              return;
            }
            delete[] t;
          }
          double timeSpentAvg=0;
          for (int w = 0; w < 5; w++) {
            timeSpentAvg+=timeSpent[w];
          }
          timeSpentAvg/=5;
          output << n[k][l] << " " << std::fixed << std::setprecision(6) << timeSpentAvg << std::endl;
        }

      }

    }

  }

  output.close();

}


int main(int argv, char **argc) {
  sortingFunc f[4] = {insertionSort, shellSort, selectionSort, heapSort};
  quickFunc q[2] = {quickSortRecursive, quickSortIterative};

  int d=0;
  std::cout << "Test? [1/2]: ";
  std::cin >> d;
  switch (d) {
    case 1:
      basicAlgorithmsTest(f);
      break;
    case 2:
      quickSortTest(q);
      break;
    default:
      std::cout << "Sorry." << std::endl;
  }

  return 0;
}
/* vim: set ts=2 sw=2 tw=0 et :*/
