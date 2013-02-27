#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <fstream>

typedef void(*sortingFunc)(int *t, int n);

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

void showArrayOnOutput(int *t, int n) {
	for(int i = 0; i<n; ++i) {
		std::cout << t[i] << " ";
	}
	std::cout << std::endl;
}

int* getDataArray(int n, char z) {
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

void firstTest(sortingFunc f[4]) {
	std::ofstream output("results.txt");

	//first test
	//TODO: change n to smaller numbers so the test will be faster.
  int n[10] = {50000, 100000, 250000, 500000, 1000000, 2000000, 5000000, 7500000, 10000000, 15000000};
	int sets[4] = {3,4,1,5}; //descending, constant, random and V-shaped
	int *t;
	
	for(int i=0; i<10; ++i) { //for each n
		for(int j=0; j<4; ++j) { //for each data set type...
			t = getDataArray(n[i], sets[j]); //we generate it

			for(int l=0; l<4; ++l) { //for each sorting function
				clock_t begin, end;
				double timeSpent;

				int* tCopy = new int[n[i]]; //we have to copy data
				memcpy(tCopy, t, n[i]*sizeof(int));

				begin = clock(); //starting time measure
				f[l](tCopy, n[i]); //running sorting function
				end = clock(); //finishing time measure

				timeSpent = (10000*(end-begin))/CLOCKS_PER_SEC; //calculating time spent on sorting
				//printf("%.24E \n",timeSpent);
				//output.precision(std::numeric_limits<double>::digits10 + 1);
				//TODO: better output
        //TODO: or idea proposed by Marcin - use awk after tests.
        output << n[i] << ";" << sets[j] << ";" << l << ";" << std::fixed << std::setprecision(8) << timeSpent << std::endl; //output to file
				delete[] tCopy;
			}
			delete[] t; //cleaning
		}
	}
	//END OF FIRST TEST

	output.close();

}




int main(int argv, char **argc) {
	srand(time(NULL));
	sortingFunc f[4] = {insertionSort, shellSort, selectionSort, heapSort};
	
	firstTest(f);
	
	return 0;
}
