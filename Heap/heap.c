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

void remove_min_recursive(int **A, size_t *n) {
    (*A)[0] = (*A)[(*n)-1];
    (*n)--;
    // the realloc is not essential, but decreases the amount of memory needed
    *A = (int*)realloc(*A, sizeof(int)*(*n));
    heapify_recursive(*A,0,*n);
}

void remove_min_iterative(int **A, size_t *n) {
    (*A)[0] = (*A)[(*n)-1];
    (*n)--;
    *A = (int*)realloc(*A, sizeof(int)*(*n));
    heapify_iterative(*A,0,*n);
}

void decrease_key(int *A, size_t i, const int value) {

    //assert(A[i] > value);
    A[i] = value;
    while ((!is_root(i))&&(A[parent(i)]>A[i])) {
        swap(A, i, parent(i));
        i = parent(i);
    }
}

void insert(int **A, const int value, size_t *n) {

    (*n)++;
    // the realloc is essential
    *A = (int*)realloc(*A, sizeof(int)*(*n));
    (*A)[(*n)-1] = D+1;
    decrease_key(*A, (*n)-1, value);

}

int* build_heap_iterative(int* A, const size_t n) {
    if(n != 0) {
        const int bound = parent(n);
        for (int i = bound; i >= 0; i--) {
            heapify_iterative(A, i, n);
        }
    }

    return A;
}

int* build_heap_recursive(int* A, const size_t n) {
    if(n != 0) {
        const int bound = parent(n);
        for (int i = bound; i >= 0; i--) {
            heapify_recursive(A, i, n);
        }
    }

    return A;
}

void heapify_recursive(int* A, const size_t i, const size_t n) {
    size_t m = i;
    size_t bottom = left(i);
    size_t top = right(i);

    // check if property is satisfied
    for (size_t j = bottom; j <= top; j++) {
        if(is_valid(A,j,n)) {
            if ((A[j]<=A[m])) {
                m = j;
            }
        }

    }
    // if not, swap and heapify again
    if(i != m) {
        swap(A,i,m);
        heapify_recursive(A,m,n);
    }
}

void heapify_iterative(int* A, size_t i, const size_t n) {

    int flag = 0;

    do {

      flag = 1;
      size_t m = i;
      size_t bottom = left(i);
      size_t top = right(i);

      for (size_t j = bottom; j <= top; j++) {
          if(is_valid(A,j,n)) {
              if ((A[j]<=A[m])) {
                  m = j;
              }
          }
      }

      if(i != m) {
        flag = 0;
        swap(A,i,m);
        i = m;
      }

    } while(flag == 0);
}

int* build_max_heap(int* A, const size_t n) {

    if(n != 0) {
        const int bound = parent(n);
        for (int i = bound; i >= 0; i--) {
            heapify_max(A, i, n);
        }
    }

    return A;
}

// only iterative version
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
        swap(A,i,m);
        i = m;
      }

    } while(flag == 0);
}

// sorting with a max heap
void heap_max_sort(int *A, const size_t n){

  A = build_max_heap(A, n);

  for (int i = n-1; i >= 0; i--) {
    swap(A,0,i);
    heapify_max(A,0,i);
  }
}
