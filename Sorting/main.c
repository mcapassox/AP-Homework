#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "sorting_methods.h"

#define REPETITIONS 20
#define BILLION 1E9

void normal_case(float **M, const size_t n){

  struct timespec requestStart, requestEnd;
  double accum;

  printf("n = %lu\n\n", n);
  printf("Insertion\tQuick\t\tCounting\tRadix\t\tBucket\t\tSelect\n");

  // measure time of insertion sort
  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {

    clock_gettime(CLOCK_REALTIME, &requestStart);
    insertion_sort(M[0], n);
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    if(i!=REPETITIONS-1)
      copy(M[7], M[0], n);

    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }
  printf("%lf\t", (accum / REPETITIONS));

  // measure time of quicksort
  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {

    clock_gettime(CLOCK_REALTIME, &requestStart);
    quick_sort(M[1], 0, n-1);
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    if(i!=REPETITIONS-1)
      copy(M[7], M[1], n);

    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }
  printf("%lf\t", (accum / REPETITIONS));

  // measure time of counting_sort
  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {
    size_t max = find_max(M[2], n);

    clock_gettime(CLOCK_REALTIME, &requestStart);
    counting_sort(M[2], max, n);
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    if(i!=REPETITIONS-1)
      copy(M[7], M[2], n);

    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }
  printf("%lf\t", (accum / REPETITIONS));

  // measure time of radix sort
  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {

    clock_gettime(CLOCK_REALTIME, &requestStart);
    radix_sort(M[3],n);
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    if(i!=REPETITIONS-1)
      copy(M[7], M[3], n);

    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;

  }
  printf("%lf\t", (accum / REPETITIONS));

  // measure time of bucket_sort
  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {

    clock_gettime(CLOCK_REALTIME, &requestStart);
    bucket_sort(M[4],n);
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    if(i!=REPETITIONS-1)
      copy(M[8], M[4], n);
    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;

  }
  printf("%lf\t", (accum / REPETITIONS));

  // look for the n/3th smallest number in the array
  size_t k = n/2+1;
  // and save it in variable val
  float val = 0;

  // measure time of select_sort sort
  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {

    clock_gettime(CLOCK_REALTIME, &requestStart);
    val = select_sort(M[5],k,0,n-1);
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    if(i!=REPETITIONS-1)
      copy(M[7], M[5], n);
    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;

  }

  printf("%lf,\n", (accum / REPETITIONS));

  // perform insertion sort on the array used by bucket sort (for correctness)
  insertion_sort(M[8],n);

  if (is_same(M[0],M[1],n)&&(is_same(M[0],M[2],n))&&(is_same(M[0],M[3],n))&&(is_same(M[4],M[8],n))&&(M[0][k]==val))
    printf("Correct\n");
  else
    printf("Wrong\n");
}

void worst_case_IQ(float **M, const size_t n){

  struct timespec requestStart, requestEnd;
  double accum;

  // sort the array and reverse it
  insertion_sort(M[0],n);
  invert_array(M[0], M[0],n);

  copy(M[0],M[1],n);

  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {
    clock_gettime(CLOCK_REALTIME, &requestStart);
    insertion_sort(M[0], n);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    if(i!=REPETITIONS-1)
    copy(M[1], M[0], n);

    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }

  //printf("%lf\t", (accum / REPETITIONS));
  printf("%lf,", (accum / REPETITIONS));

  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {
    clock_gettime(CLOCK_REALTIME, &requestStart);
    quick_sort(M[1], 0, n-1);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    if(i!=REPETITIONS-1)
      invert_array(M[1], M[1],n);

    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }
  //printf("%lf\t", (accum / REPETITIONS));
  printf("%lf\n", (accum / REPETITIONS));

  /*if (is_same(M[0],M[1],n))
    printf("Correct\n");
  else
    printf("Wrong\n");*/
}

void best_case_IQ(float **M, const size_t n){

  struct timespec requestStart, requestEnd;
  double accum;

  // sort it
  insertion_sort(M[0],n);
  copy(M[0],M[1],n);

  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {
    clock_gettime(CLOCK_REALTIME, &requestStart);
    insertion_sort(M[0], n);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    copy(M[1], M[0], n);
    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }

  //printf("%lf\t", (accum / REPETITIONS));
  printf("%lf,", (accum / REPETITIONS));
  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {
    clock_gettime(CLOCK_REALTIME, &requestStart);
    quick_sort_best(M[1], 0, n-1);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }

  //printf("%lf\t", (accum / REPETITIONS));
  printf("%lf\n", (accum / REPETITIONS));

  /*if (is_same(M[0],M[1],n))
    printf("Correct\n");
  else
    printf("Wrong\n");*/
}


int main(int argc, char *argv[]) {

  if(argc < 2){
    printf("One need to be passed: n. RETURNING. \n");
    return -1;
  }

  size_t n = atoi(argv[1]);

  float **M = (float**)malloc(sizeof(float*)*(9));

  for (size_t i = 0; i < 9; i++) {
    M[i] = (float *)malloc(sizeof(float) * (n));
  }


  const size_t d = n;

  build_problem_instance(M[0], n, d);
  build_problem_instance_prob(M[4], n, 1);

  // M[8] is the backup for bucket sort
  for (size_t i = 1; i < 9; i++) {
    if((i!=4)&&(i!=8))
    copy(M[0],M[i],n);
  }

  copy(M[4], M[8], n);

  normal_case(M,n);
  //printf("\n");
  //worst_case_IQ(M,n);
  //printf("\n");
  //best_case_IQ(M, n);
  //printf("\n");

  for (size_t i = 0; i < 9; i++) {
    free(M[i]);
  }
  free(M);


}
