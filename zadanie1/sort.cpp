#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>

int* insertionSort(int *t, int n) {
	for(int i = 1; i<n; ++i) {
		int v = t[i];
		int j;

		for(j = i-1; j>=0 && t[j]>v; --j) {
			t[j+1] = t[j];
		}

		t[j+1] = v;
	}
	return t;
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

void showTableOnOutput(int *t, int n) {
	for(int i = 0; i<n; ++i) {
		std::cout << t[i] << " ";
	}
	std::cout << std::endl;
}

int* getRandomDataArray(int n) {
	int *t = new int[n];
	for(int i = 0; i<n; i++) {
		t[i] = rand()%100;
	}
	return t;
}

int main(int argv, char **argc) {
	srand(time(NULL));
	const int n = 10;


	int *t = getRandomDataArray(n);
	std::cout << std::setw(20) << "UNSORTED: ";
	showTableOnOutput(t, n);

	//INSERTION SORT
	int *t_insert = new int[n];
	memcpy(t_insert, t, n*sizeof(int));
	insertionSort(t_insert, n);
	std::cout << std::setw(20) << "INSERTION SORT: ";
	showTableOnOutput(t_insert, n);
	delete[] t_insert;
	//END OF INSERTION SORT

	//SHELL SORT
	int *t_shell = new int[n];
	memcpy(t_shell, t, n*sizeof(int));
	shellSort(t_shell, n);
	std::cout << std::setw(20) << "SHELL SORT: ";
	showTableOnOutput(t_shell, n);
	delete[] t_shell;
	//END OF SHELL SORT

	//SELECTION SORT
	int *t_selection = new int[n];
	memcpy(t_selection, t, n*sizeof(int));
	selectionSort(t_selection, n);
	std::cout << std::setw(20) << "SELECTION SORT: ";
	showTableOnOutput(t_selection, n);
	delete[] t_selection;
	//END OF SELECTION SORT

	//HEAP SORT
	int *t_heap = new int[n];
	memcpy(t_heap, t, n*sizeof(int));
	heapSort(t_heap, n);
	std::cout << std::setw(20) << "HEAP SORT: ";
	showTableOnOutput(t_heap, n);
	delete[] t_heap;

	//CLEANING
	delete[] t; t=NULL;
	
	return 0;
}