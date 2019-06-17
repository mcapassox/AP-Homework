#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "heap.h"


#define REPETITIONS 100
#define BILLION 1E9
#define D 10000


void recursive_case(int *A, size_t n) {

    //printf("Building heap: \n");

    A = build_heap_recursive(A,n);

    //print_structure(A,n);
    //printf("\n");

    //printf("Removing minimum: \n");
    remove_min_recursive(&A, &n);
    //print_structure(A,n);
    //printf("\n");

    /*printf("Decrease key: \n");
    decrease_key(A, 4, 1);
    //print_structure(A,n);
    printf("\n");

    printf("Inserting 300: \n");
    insert(&A, 300, &n);
    //print_structure(A,n);
    printf("\n");*/

}

void iterative_case(int *A, size_t n) {

    //printf("Building heap: \n");

    A = build_heap_iterative(A,n);
    //print_structure(A,n);
    //printf("\n");

    //printf("Removing minimum: \n");
    remove_min_iterative(&A, &n);
    //print_structure(A,n);
    //printf("\n");
}



int main(int argc, char *argv[]) {
    struct timespec requestStart, requestEnd;
    double accum;

    if(argc < 2) {
        printf("One need to be passed: n. RETURNING. \n");
        return -1;
    }
    size_t n = atoi(argv[1]);


    int *A = (int*)malloc(sizeof(int)*n);
    int *B = (int*)malloc(sizeof(int)*n);
    int *E = (int*)malloc(sizeof(int)*n);


    build_problem_instance(A,n,D);
    copy(A,B,n);
    copy(A,E,n);

    //printf("Printing original array: ");
    //print(A,n);
    //printf("\n");


    // test running time for recursive case
    accum = 0;
    for (size_t i = 0; i < REPETITIONS; i++) {
        clock_gettime(CLOCK_REALTIME, &requestStart);
        recursive_case(A, n);
        clock_gettime(CLOCK_REALTIME, &requestEnd);
        if (i!=REPETITIONS-1) {
          copy(E,A,n);
        }
        accum += (requestEnd.tv_sec - requestStart.tv_sec) +
                 (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
    }
    printf("%lf,", (accum / REPETITIONS));

    // test running time for iterative case
    accum = 0;
    for (size_t i = 0; i < REPETITIONS; i++) {
        clock_gettime(CLOCK_REALTIME, &requestStart);
        iterative_case(B, n);
        clock_gettime(CLOCK_REALTIME, &requestEnd);
        if (i!=REPETITIONS-1) {
          copy(E,B,n);
        }
        accum += (requestEnd.tv_sec - requestStart.tv_sec) +
                 (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
    }
    printf("%lf\n", (accum / REPETITIONS));

    // check for correctness
    if (is_same(A,B,n)) {
      printf("Correct\n");
    }
    else
      printf("Wrong\n");



    free(A);
    free(B);
    free(E);

    return 0;

}
