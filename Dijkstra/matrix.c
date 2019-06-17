#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

void swap(node* A, const size_t i, const size_t j){
  const node temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

void print_vec_node(const node* A, const size_t n){
  for (size_t i = 0; i < n; i++) {
    printf("[%0.f, %lu] ", A[i].key, A[i].heap_id);
  }
}

void print_vec(const float* A, const size_t n){
  for (size_t i = 0; i < n; i++) {
    printf("[%0.f] ", A[i]);
  }
}

void copy(const node *A, node *B, const size_t n){
  for (size_t i = 0; i < n; i++) {
    B[i] = A[i];
  }
}

void allocate(float **A, const size_t n){
  for (size_t i = 0; i < n; i++) {
    A[i] = (float *)malloc(sizeof(float) * (n));
  }
}

size_t find_max(const float *A, const size_t n) {
    size_t max = A[0];
    for (size_t i = 1; i < n; i++) {
        if (max < A[i]) {
            max = A[i];
        }
    }
    return max;
}

 void build_problem_instance(float **A, const size_t n, const size_t max) {
    for (size_t i = 0; i < n; i++) {
      A[i][i] = 0;
      for (size_t j = 0; j < i; j++) {
        float val = rand() % max;
        A[i][j] = val;
        A[j][i] = val;
      }
    }
}

float is_same(const float *A, const float *B, const size_t n){
  for (size_t i = 0; i < n; i++) {
    if (A[i] != B[i]) {
      return 0;
    }
  }
  return n;
}

// print matrix
void print(float **A, const size_t n){
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      printf("%0.f ", A[i][j]);
    }
    printf("\n");
  }
}

void free_mat(float **A, const size_t n){
    for (size_t i = 0; i < n; i++) {
      free(A[i]);
    }
    free(A);
}
