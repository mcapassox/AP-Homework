#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

 void build_problem_instance(int *A, const size_t n, const size_t d) {
    for (size_t i = 0; i < n; i++) {
        A[i] = rand() % d+1;
    }
}

void swap(int *A, const size_t i, const size_t j){
  const int temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

int find_max(int* A, const size_t n){
  int max = A[0];
  for (size_t i = 0; i < n; i++) {
    if(max < A[i])
      max = A[i];
  }
  return max;
}

void print(const int *A, const size_t n){
  for (size_t i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n" );
}

void print_structure(const int *A, const size_t n){
  size_t counters[n];
  counters[0] = 0;
  size_t index = 0;
  for (size_t i = 0; i < n; i++) {
    counters[i+1] = counters[i] + pow(2,i+1);
  }

  for (size_t i = 0; i < n; i++) {
    printf("%d ", A[i]);
    if (i == counters[index]) {
      printf("\n" );
      index++;
    }
  }
  printf("\n" );
}

int is_same(int *A, int *B, const size_t n){
  for (size_t i = 0; i < n; i++) {
    if (A[i]!=B[i]) {
      return 0;
    }
  }
  return 1;
}

void copy(int *A, int *B,const size_t n){
  for (size_t i = 0; i < n; i++) {
    B[i] = A[i];
  }
}
