#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// copy function
void copy(const float *A, float *B, const size_t n){
  for (size_t i = 0; i < n; i++) {
    B[i] = A[i];
  }
}

// find max
size_t find_max(const float *A, const size_t n) {
    size_t max = A[0];
    for (size_t i = 1; i < n; i++) {
        if (max < A[i]) {
            max = A[i];
        }
    }
    return max;
}

// build problem instance (numbers between 1 and max num)
 void build_problem_instance(float *A, const size_t n, const size_t d) {
    for (size_t i = 0; i < n; i++) {
        A[i] = rand() % d+1;
    }
}

// build probabilistic problem instance (between 0 and 1)
 void build_problem_instance_prob(float *A, const size_t n, const size_t d) {
    for (size_t i = 0; i < n; i++) {
        A[i] = (float)rand() / (float)RAND_MAX ;
    }
}

// correctness check function
float is_same(const float *A, const float *B, const size_t n){
  for (size_t i = 0; i < n; i++) {
    if (A[i] != B[i]) {
      return 0;
    }
  }
  return n;
}

// invert array function 
void invert_array(const float *A, float *B, const size_t n){

  float *Z = (float*)malloc((float)sizeof(float)*n);

  for (size_t i = 0; i < n; i++) {
    Z[i] = A[i];
  }
  for (size_t i = 0; i < n; i++) {
    B[n-1-i] = Z[i];
  }
  free(Z);
}
