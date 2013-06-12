#ifndef UTILS_H

#define UTILS_H
#include <time.h>

int* generate_unique_array(int size, int even);
void print_array(int *arr, int size);
double timespec_to_miliseconds(struct timespec *begin, struct timespec *end);
//int *generate_unique_array_odd(int size);
#endif /* end of include guard: UTILS_H */
