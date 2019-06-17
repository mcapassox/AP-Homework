#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "matrix.h"
#include "heap.h"

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

unsigned int is_valid(node* A, const size_t i, const size_t n) {
    return (n > i);
}

void remove_min_recursive(node **A, node** dist, size_t *n) {
    (*A)[0] = (*A)[(*n)-1];
    (*n)--;
    *A = (node*)realloc(*A, sizeof(node)*(*n));
    heapify_recursive(*A,*dist,0,*n);
}

void build_heap_recursive(node* A, node* dist, const size_t n) {
    if(n != 0) {
        const size_t bound = parent(n);
        for (int i = bound; i >= 0; i--) {
            heapify_recursive(A,dist, i, n);
        }
    }
}

void heapify_recursive(node* A, node* dist, const size_t i, const size_t n) {
    size_t m = i;
    size_t bottom = left(i);
    size_t top = right(i);
    for (size_t j = bottom; j <= top; j++) {
        if(is_valid(A,j,n)) {
            if ((A[j].key<A[m].key)) {
                m = j;
            }
        }

    }
    if(i != m) {
        // keep track of heap index
        dist[A[i].id].heap_id = m;
        dist[A[m].id].heap_id = i;
        swap(A,i,m);
        heapify_recursive(A,dist,m,n);
    }
}

void decrease_key(node *A, size_t i, const float value) {
    //assert(A[i].key > value);
    A[i].key = value;
    while ((!is_root(A[i].id))&&(A[parent(i)].key>A[i].key)) {
        swap(A, i, parent(i));
        i = parent(i);
    }
}

void print_heap(node *heap, const size_t n){
  for (size_t i = 0; i < n; i++) {
    printf("[%0.f, %lu] ", heap[i].key, heap[i].id);
  }
  printf("\n");
}
