#include <cstdio>
#include <cstdlib>
#include <list>
#define VERBOSE

inline int max(int a, int b) {
	return (a>b)?a:b;
}

void knapsack_dynamic(int n, int capacity, int *value, int *weight) {
	//table initialization
	int **dyntable = (int**)calloc(n+1, sizeof(int*));
	for(int i=0; i<=n; i++)
		dyntable[i] = (int*)calloc(capacity+1, sizeof(int));
	//end of table initialization

  //main part of the algorithm
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=capacity; j++) {
      //weight[i-1] and value[i-1] is because of weight and value being arrays from 0 to n-1
      dyntable[i][j] = (j<weight[i-1])? 
        dyntable[i-1][j]:max(dyntable[i-1][j], dyntable[i-1][j-weight[i-1]]+value[i-1]);
    }
	}
  //once we have completed filling our table, we can read the solution


#ifdef VERBOSE
  printf("Max value is: %d\n",dyntable[n][capacity]);
  /*for(int i=0; i<n+1; i++) {
    for(int j=0; j<capacity+1; j++) {
      printf("%d ",dyntable[i][j]);
    }
    printf("\n");
  }*/
  printf("The solution is: ");
  int i=n, j=capacity;
  while(dyntable[i][j]!=0) {
    if(dyntable[i-1][j]!=dyntable[i][j]) {
      printf("%d ",i);
      j-=weight[i-1];
    }
    i--;
  }
  printf("\n");
#endif
  for(int i=0; i<=n; i++) free(dyntable[i]);
  free(dyntable);
} //end of knapsack dynamic

void knapsack_bruteforce
  (int id, int sum_weight, int sum_value, int capacity, int n, int *value, 
  int *weight, bool *result, bool *temp, int *best) {
  if(sum_weight>capacity) return; //there is no reaaasooon
  if(id<n) { //if there are more items to check
    //decision: false
    temp[id+1]=false; //our algorithm is not paralell, so we can use single temporary array for every call
    knapsack_bruteforce(id+1, sum_weight, sum_value, 
      capacity, n, value, weight, result, temp, best);

    //decision: true
    temp[id+1]=true;
    knapsack_bruteforce(id+1, sum_weight+weight[id+1], 
      sum_value+value[id+1], capacity, n, value, weight, result, temp, best);
  }else{ //each item is checked.
    if(sum_value>(*best)) {
      *best = sum_value;
      for(int i=0; i<=n; i++) {
        result[i] = temp[i];
      }
    }
  }
}

void knapsack_bf_iface(int n, int capacity, int *value, int *weight) {
  bool *result = (bool*)calloc(n+1, sizeof(bool));
  bool *temp = (bool*)calloc(n+1, sizeof(bool));
  int best=0; //some variables
  //first call of knapsack_bruteforce with default values
  knapsack_bruteforce(-1, 0, 0, capacity, n, value, weight, result, temp, &best);

#ifdef VERBOSE
  printf("Max value is: %d\n", best);
  printf("The solution is: ");
  for(int i=0; i<=n; i++) 
    if(result[i]) printf("%d ",i+1);
  printf("\n");
#endif

  free(result);
  free(temp);
}


int main(int argc, char** argv) {
  int value[5] = {1,10,5,6,2};
  int weight[5] = {1,4,3,2,1};
  int capacity = 8;

  printf("DYNAMIC: \n");
  knapsack_dynamic(5, capacity, value, weight);
  printf("\n\nBRUTE FORCE: \n");
  knapsack_bf_iface(5, capacity, value, weight);
#ifdef _WIN32 || _WIN64
  system("pause");
#endif
  return 0;
}
