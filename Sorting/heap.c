#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "heap.h"
#include "matrix.h"

#define D 1000

size_t left(const size_t i) {
    return 2*i+1;
}

size_t right(const size_t i) {
    return 2*i+2;
}

size_t parent(const size_t i) {
    return i/2;
}

size_t get_root() {
    return 0;
}

size_t is_root(size_t i) {
    return i == 0;
}

unsigned int is_valid(int* A, const size_t i, const size_t n) {
    return (n > i);
}

int min(int *A) {
    return A[0];
}

// swap integers
void swap_int(int *A, const size_t index1, const size_t index2) {
   const int temp = A[index1];
   A[index1] = A[index2];
   A[index2] = temp;
}

// build max heap (instead of min heap)
int* build_max_heap(int* A, const size_t n) {
    if(n != 0) {
        const int bound = parent(n);
        for (int i = bound; i >= 0; i--) {
            heapify_max(A, i, n);
        }
    }

    return A;
}

// only iterative version for max heap
void heapify_max(int* A, size_t i, const size_t n) {

    int flag = 0;

    do {

      flag = 1;
      size_t m = i;
      size_t bottom = left(i);
      size_t top = right(i);

      for (size_t j = bottom; j <= top; j++) {
          if(is_valid(A,j,n)) {
              if ((A[j]>=A[m])) {
                  m = j;
              }
          }
      }

      if(i != m) {
        flag = 0;
        swap_int(A,i,m);
        i = m;
      }

    } while(flag == 0);
}

//  heap sort
void heap_max_sort(int *A, const size_t n){

  A = build_max_heap(A, n);

  for (int i = n-1; i >= 0; i--) {
    swap_int(A,0,i);
    heapify_max(A,0,i);
  }
}
