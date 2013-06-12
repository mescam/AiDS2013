#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
struct knapsack_data {
  int *value;
  int *weight;
  int c,n;
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

unsigned long long int temp_x=0, res_x=0;
int best=0;

void knapsack_bruteforce
(int id, int sum_weight, int sum_value, int capacity, int n, int *value, 
 int *weight) {
#ifndef NONSENSE
  if(sum_weight>capacity) return; //there is no reaaasooon
#endif
  if(id<n-1) { //if there are more items to check
    //decision: false
    //our algorithm is not paralell, so we can use single temporary var for every call
    temp_x &= ~(1ull << (id+1));
    knapsack_bruteforce(id+1, sum_weight, sum_value, 
        capacity, n, value, weight);

    //decision: true
    temp_x |= (1ull << (id+1));
    knapsack_bruteforce(id+1, sum_weight+weight[id+1], 
        sum_value+value[id+1], capacity, n, value, weight);
  }else{ //each item is checked.
    if(sum_value>best) {
      res_x=temp_x;
      best=sum_value;
    }
  }
}

void knapsack_bf_iface(int n, int capacity, int *value, int *weight) {
  //first call of knapsack_bruteforce with default values
  knapsack_bruteforce(-1, 0, 0, capacity, n, value, weight);
#ifdef VERBOSE
  printf("Max value is: %d\n", best);
  printf("The solution is: ");
  //printf("res_x: %lld\n\n",res_x);
  for(int i=0; i<=n; i++) {
    if(res_x%2) printf("%d ", i+1);
    res_x=res_x>>1;
  }
  printf("\n");
#endif
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

#define TESTS 100

void test_const_c() {
  int c = 15;
  int n[15] = {20,30,40,50,60,70,80,90,100,110,120,130,140,150,160};
  std::ofstream res("res1.txt");
  res << "0 0 0" << std::endl;
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
      knapsack_bf_iface(n[i]/10, c, d.value, d.weight);
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
  int c[15] = {100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500};
  std::ofstream res("res2.txt");
  res << "0 0 0" << std::endl;
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

knapsack_data load() {
  std::ifstream plik("data.txt");
  knapsack_data d;
  int i=0;
  plik>>d.c;
  plik>>d.n;
  //int *price, *weight;
  d.value = (int*)calloc(d.n,sizeof(int));
  d.weight = (int*)calloc(d.n,sizeof(int));
  while(!plik.eof()){
    plik >> d.value[i] >> d.weight[i];
    i++;
  }
  return d;
}

void turniej(knapsack_data d) {
  timespec begin, end;
  //printf("c=%d n=%d\n",d.c, d.n);
  //for(int i=0; i<d.n; i++) printf("p[%d]=%d w[%d]=%d\n",i,d.value[i],i,d.weight[i]);
  clock_gettime(CLOCK_REALTIME, &begin);
  knapsack_bf_iface(d.n,d.c,d.value,d.weight);
  clock_gettime(CLOCK_REALTIME, &end);
  printf("Czas działania: %f\n",timespec_to_seconds(&begin, &end));
  printf("Max value is: %d\n", best);
  printf("The solution is: ");
  //printf("res_x: %lld\n\n",res_x);
  for(int i=0; i<=d.n; i++) {
    if(res_x%2) printf("%d ", i+1);
    res_x=res_x>>1;
  }
  printf("\n");

  free(d.value); free(d.weight);
}

int main(int argc, char** argv) {
  srand(time(0));

  if(argc>1) {
    switch(argv[1][0]) {
      case '1': 
        test_const_c();
        printf("const c test done\n");
        break;
      case '2':
        test_const_n();
        printf("const n test done\n");
        break;
      case '3': {
        knapsack_data d = load();
        turniej(d);
        break;
                }
      case '4': {
        knapsack_data d = generate(10);
        knapsack_dynamic(10,10,d.value,d.weight);
        knapsack_bf_iface(10,10,d.value,d.weight);
        break;
                }
      case '5':
        printf("%ld\n",sizeof(unsigned long long int));
        break;
    }
  }
  return 0;
}
