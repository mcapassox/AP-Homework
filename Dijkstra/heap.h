#include "struct.h"

size_t left(const size_t i);
size_t right(const size_t i);
size_t parent(const size_t i);
size_t get_root();
size_t is_root(size_t i);
unsigned int is_valid(node *A, const size_t i, const size_t n);
void build_heap_recursive(node* A, node* dist, const size_t n);
void heapify_recursive(node* A, node* dist, const size_t i, const size_t n);
void remove_min_recursive(node **A, node **dist, size_t *n);
void decrease_key(node *A, size_t i, const float value);
void print_heap(node *heap, const size_t n);
