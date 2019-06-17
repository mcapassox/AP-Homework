#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

// swap function
void swap(float *A, const size_t index1, const size_t index2) {
  const float temp = A[index1];
  A[index1] = A[index2];
  A[index2] = temp;
}

// insertion sort function
void insertion_sort(float *A, const size_t n) {
  for (int i = 0; i < n; i++) {
     int j = i;
     // swap back until in right position
     while (j > 0 && A[j] < A[j - 1]) {
       swap(A, j - 1, j);
       j--;
     }
   }
}

// partition function
size_t partition(float* A, size_t i, size_t j, size_t p) {

    // swap with pivot
    swap (A,i,p);
    p = i;

    // handle duplicates
    int check = 0;

    while (i<=j) {
        // if greater than pivot swap element to the r
        if (A[i]>A[p]) {
            swap(A,i,j);
            j--;
        }
        else if (A[i] == A[p]){
          // if it's not a duplicate
          if (check) {
            swap(A, i, j);
            j--;
            check = 0;
          // if it's a duplicate
          } else {
            i++;
            check = 1;
          }
        }
        else
          i++;
    }

    swap(A,p,j);
    return j;
}

// quick sort function
void quick_sort(float * A, int l, const int r) {
  size_t p;
  while(l<r) {
    // partition array using first element as pivot
    p = partition(A, l, r, l);
    // recursive call on first partition of the array
    quick_sort(A, l, p-1);
    l = p + 1;
  }
}

void quick_sort_best(float * A, int l, const int r) {
   size_t p;
   while(l<r) {
       // partition array always using the mid element of the array as pivot
       p = partition(A, l, r, (l+r)/2);
       quick_sort_best(A, l, p-1);
       l = p + 1;
   }
}

void counting_sort(float *A, const size_t k, const size_t n) {

    float *B = (float *)malloc(sizeof(float) * (n));
    float *C = (float *)malloc(sizeof(float) * (k));

    // index counts = 0
    for (size_t i = 0; i < k; i++) {
        C[i] = 0;
    }

    // increase index count for each element
    for (size_t i = 0; i < n; i++) {
        const int index = A[i];
        C[index-1] += 1;
    }

    // sum up the indeces
    for (size_t j = 0; j < k-1; j++) {
        C[j+1] += C[j];
    }


    for (int i = n-1; i >= 0; i--) {
        const int index1 = A[i];
        const int index2 = C[index1-1];
        // write in B the result
        B[index2-1] = index1;
        // decrease index
        C[index1-1] -= 1;
    }

    // copy back array
    for (size_t i = 0; i < n; i++) {
        A[i] = B[i];
    }

    free(B);
    free(C);
}

void counting_sort_radix(float *A, const size_t k, const size_t n, const size_t exp) {

    float *B = (float *)malloc(sizeof(float) * n);
    float *C = (float *)malloc(sizeof(float) * 10);

    for (size_t i = 0; i < 10; i++) {
        C[i] = 0;
    }

    for (size_t i = 0; i < n; i++) {
        size_t index = A[i]/exp;
        index = index%10;
        C[index]++;
    }

    for (size_t j = 0; j < 9; j++) {
        C[j+1] += C[j];
    }

    for (int i = n-1; i >= 0; i--) {
        size_t index1 = A[i]/exp;
        index1 = index1%10;
        size_t index2 = C[index1];
        B[index2-1] = A[i];
        C[index1]--;
    }

    for (size_t i = 0; i < n; i++) {
        A[i] = B[i];
    }

    free(C);
    free(B);
}

 void radix_sort(float *A, const size_t n) {
    // find greatest order of magnitude
    int m = find_max(A,n);
    // call radix sort for each digit
    for (size_t i = 1; m/i > 0; i*=10) {
        counting_sort_radix(A,m,n,i);
    }
}

void bucket_sort(float *A, const size_t n) {
    // create n buckets
    float **B = (float **)malloc(sizeof(float *) * (n));

    for (size_t i = 0; i < n; i++) {
    // each bucket can have max dimension n
        B[i] = (float *)malloc(sizeof(float) * n);
    }

    // initialize with 2s
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            B[i][j] = 2;
        }
    }


    for (size_t i = 0; i < n; i++) {
        size_t counter = 0;
        // map from 0-1 to 1 - 10
        size_t index = (int)(A[i]*10);

        // map to the correct bucket index
        index = index/(10/(float)n);
        while(B[counter][index] != 2) {
            counter++;
        }

        B[counter][index] = A[i];
    }

    // position in the final sorted array
    size_t counter = 0;

    // number of elements in each bucket
    size_t counter2;

    for (size_t i = 0; i < n; i++) {
        counter2 = 0;
        while ((counter2<n)&&(B[counter2][i]!=2)) {
            counter2++;
        }

        if (counter2!=0) {
            // each bucket is to be sorted
            float *toBeconverted = (float*)malloc(sizeof(float)*(counter2));
            counter2 =0;
            while ((counter2<n)&&(B[counter2][i]!=2)) {
                toBeconverted[counter2] = B[counter2][i];
                counter2++;
            }

            // sort it
            insertion_sort(toBeconverted,counter2);
            for (size_t l = 0; l < counter2; l++) {
                if (toBeconverted[l]!=2) {
                    A[counter] = toBeconverted[l];
                    counter++;
                }
            }
            free(toBeconverted);
        }
    }
    for (size_t i = 0; i < n; i++) {
        free(B[i]);
    }
    free(B);
}


size_t select_pivot(float* A, const size_t l, const size_t r)
{

  // number of chunks
  unsigned int chunks = (r - l) / 5 + 1;

  // return the median of the last chunk
  if (r - l + 1 <= 5) {
    quick_sort(A, l, r);
    return (l + r) / 2;
  }

  // counter to iterate through chunks
  size_t counter = l + 4;
  // sort all the chunks
  while (counter < r - 5) {
    quick_sort(A, counter - 4, counter);
    if (counter + 5 >= r - 5)
      counter = r;
    else
      counter += 5;
  }

  // put at the beginning of the array the median of each chunk
  size_t j = l + 5;

  for (size_t i = l; i < chunks; i++) {
    swap(A, i, (j + i * 5) / 2);
    if (j + 5 >= r)
      j = r;
    else
      j += 5;
  }

  size_t toBeReturned;
  // iterate till you have just one chunk
  toBeReturned = select_pivot(A, l, l + chunks);
  return toBeReturned;
}

 float select_sort(float *A, const size_t i, const size_t l, const size_t r) {

    // select_sort best choice pivot
    size_t j = select_pivot(A, l, r);

    // partition around pivot
    size_t k = partition(A,l,r,j);

    if(i == (k+1))
    {
      return A[k];
    }

    // look in left/right part of the array
    if (i < (k+1))
        return select_sort(A,i,l,k-1);
    else
        return select_sort(A,i,k+1,r);
}
