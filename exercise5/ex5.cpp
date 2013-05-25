#include <cstdio>
#include <cstdlib>
#include <ctime>
#define NONSENSE

#ifdef NONSENSE
#include <fstream>
#endif

struct knapsack_data {
  int *value;
  int *weight;
};

double timespec_to_seconds(timespec *begin, timespec *end) {
  return (double) (end->tv_sec - begin->tv_sec)
    +1.e-9*(end->tv_nsec - begin->tv_nsec);
}

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
#ifndef NONSENSE
  if(sum_weight>capacity) return; //there is no reaaasooon
#endif
  if(id<n-1) { //if there are more items to check
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


knapsack_data generate(int n) {
  knapsack_data result;
  result.value = (int*)calloc(n,sizeof(int));
  result.weight = (int*)calloc(n,sizeof(int));
  for(int i = 0; i < n; ++i) {
    result.value[i] = rand()%10+1;
    result.weight[i] = rand()%10+1;
  }
  return result;
}

#define TESTS 5

void test_const_c() {
  int c = 20;
  int n[15] = {20,30,40,50,60,70,80,90,100,110,120,130,140,150,160};
  std::ofstream res("res1.txt");
  for(int i=0; i<15; i++) {
    double a=0, b=0;
    timespec begin, end;
    for(int j=0; j<TESTS; j++) {
      knapsack_data d = generate(n[i]);
      printf("TEST n=%d #%d\n",n[i],j);
      
      //dynamic
      clock_gettime(CLOCK_REALTIME, &begin);
      knapsack_dynamic(n[i], c, d.value, d.weight);
      clock_gettime(CLOCK_REALTIME, &end);
      a+=timespec_to_seconds(&begin, &end);
      printf("dynamic done\n");
      
      //brute force
      clock_gettime(CLOCK_REALTIME, &begin);
      knapsack_bf_iface(n[i]/5, c, d.value, d.weight);
      clock_gettime(CLOCK_REALTIME, &end);
      b+=timespec_to_seconds(&begin, &end);
      printf("brute force done\n\n\n");
      
      free(d.value); 
      free(d.weight);
    }
    a/=TESTS; b/=TESTS;
    res << n[i] << " " << a << " " << b << std::endl;
  }
  res.close();
  return;
}

void test_const_n() {
  int n = 15;
  int c[15] = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};
  std::ofstream res("res2.txt");
  for(int i=0; i<15; i++) {
    double a=0, b=0;
    timespec begin, end;
    for(int j=0; j<TESTS; j++) {
      knapsack_data d = generate(n);
      printf("TEST c=%d #%d\n",c[i],j);

      //dynamic
      clock_gettime(CLOCK_REALTIME, &begin);
      knapsack_dynamic(n, c[i], d.value, d.weight);
      clock_gettime(CLOCK_REALTIME, &end);
      a+=timespec_to_seconds(&begin, &end);
      printf("dynamic done\n");

      //brute force
      clock_gettime(CLOCK_REALTIME, &begin);
      knapsack_bf_iface(n, c[i], d.value, d.weight);
      clock_gettime(CLOCK_REALTIME, &end);
      b+=timespec_to_seconds(&begin, &end);
      printf("brute force done\n\n\n");
      
      free(d.weight);
      free(d.value);
    }
    a/=TESTS; b/=TESTS;
    res << c[i] << " " << a << " " << b << std::endl;
  }
  res.close();
  return;
}


int main(int argc, char** argv) {
  srand(time(0));

  if(argc>1) {
    switch(argv[1][0]) {
      case '1': 
        test_const_n();
        printf("const n test done\n");
        break;
      case '2':
        test_const_c();
        printf("const c test done\n");
        break;
      case '3':
        //from file
        break;
    }
  }
  return 0;
}
