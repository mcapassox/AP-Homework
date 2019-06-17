#include "struct.h"

void copy(const node *A, node *B, const size_t n);
size_t find_max(const float *A, const size_t n);
void build_problem_instance(float **A, const size_t n, const size_t d);
void allocate(float **A, const size_t n);
void print(float **A, const size_t n);
void free_mat(float **A, const size_t n);
void swap(node *A, const size_t i, const size_t j);
void print_vec(const float* A, const size_t n);
void print_vec_node(const node* A, const size_t n);
