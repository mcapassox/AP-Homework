size_t left(const size_t i);
size_t right(const size_t i);
size_t parent(const size_t i);
size_t get_root();
size_t is_root(size_t i);
unsigned int is_valid(int *A, const size_t i, const size_t n);
void heap_max_sort(int *A, size_t n);
void heapify_max(int* A, size_t i, const size_t n);
