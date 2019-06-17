#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "heap.h"
#include "struct.h"


#define REPETITIONS 20
#define INFINITY 9999
#define BILLION 1E9
#define MAX 10

// checking function
short unsigned int check_dist(float* dist_array, node* dist_heap, const size_t n){
  for (size_t i = 0; i < n; i++) {
    if (dist_array[i] != dist_heap[i].key) {
      return 0;
    }
  }
  return 1;
}

// check path
short unsigned int check_pred(size_t* pred_array, size_t* pred_heap, const size_t n){
  for (size_t i = 0; i < n; i++) {
    if (pred_array[i] != pred_heap[i]) {
      return 0;
    }
  }
  return 1;
}

// initialize cost function
void init_cost(float **A, float **B, const size_t n){
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (B[i][j] == 0) {
        A[i][j] = INFINITY;
      }
      else{
        A[i][j]=B[i][j];
      }
    }
  }
}


extern inline void relax_update(node* dist, node* dist_heap, size_t *pred, float **cost, size_t next, float min_dist, const size_t n){
  // check if there exists a better path to next node
  for (size_t k = 0; k < n; k++) {
    // if it hasn't been visited
    if (dist[k].visited == 0) {
      // and the distance is shorter, update distances and pred
      float new_val = min_dist + cost[next][k];
      if(new_val < dist[k].key)
      {
        dist[k].key = new_val;
        dist_heap[dist[k].heap_id].key = new_val;
        pred[k] = next;
      }
    }
  }
}

// complexity 2*n^2 + n
void dijkstra_array(float **cost, float *dist, size_t *pred, const size_t start_node, const size_t n){

  // 0 for not visited, 1 for visited
  size_t* visited = (size_t*)malloc(sizeof(size_t)*n);

  // Initialise distance, predecessor and visited vectors
  for (size_t i = 0; i < n; i++) {
    dist[i] = cost[start_node][i];
    pred[i] = start_node;
    visited[i] = 0;
  }

  // Initialise values for start_node
  dist[start_node]=0;
	visited[start_node]=1;

  for (size_t i = 0; i < n-1; i++) {
    float min_dist = INFINITY;
    size_t next;

    // find closest node
    for (size_t j = 0; j < n; j++) {
      if ((dist[j] < min_dist)&&(visited[j] == 0)) {
        min_dist = dist[j];
				next = j;
      }
    }

    // and set it as visited
    visited[next] = 1;

    // check if there exists a better path to next node
    for (size_t k = 0; k < n; k++) {
      // if it hasn't been visisted
      if (visited[k] == 0) {
        // and the distance is shorter, update distance and pred
        if(min_dist + cost[next][k] < dist[k])
        {
          dist[k] = min_dist + cost[next][k];
          pred[k] = next;
        }
      }
    }
  }

  free(visited);
}

// complexity 2*n + n * log n + n^2
void dijkstra_heap(float **cost, node *dist, size_t *pred, const size_t start_node, const size_t n){

  size_t n_heap = n;

  node* dist_heap= (node*)malloc(sizeof(node)*n);

  // Initialise distance, predecessor and visited vectors for dist e dist_heap
  for (size_t i = 0; i < n; i++) {
    dist[i].key = cost[start_node][i];
    dist[i].visited = 0;
    dist[i].heap_id = i;
    dist_heap[i].key = cost[start_node][i];
    dist_heap[i].id = i;
    pred[i] = start_node;
  }

  // initialise values for start_node
  dist[start_node].key = 0;
  dist[start_node].visited = 1;
  dist_heap[start_node].key = 0;

  // build the heap
  build_heap_recursive(dist_heap, dist, n_heap);

  while (n_heap > 1)
  {
    // remove the min and consequently heapify
    remove_min_recursive(&dist_heap, &dist, &n_heap);

    // initialise min dist and closest node
    float min_dist = dist_heap[0].key;
    size_t next = dist_heap[0].id;

    // set next as visited
    dist[next].visited = 1;

    relax_update(dist, dist_heap, pred, cost, next, min_dist, n);

  }

  free(dist_heap);
}

int main(int argc, char *argv[]) {

  struct timespec requestStart, requestEnd;
  double accum = 0;

  if(argc < 3){
    printf("Two arguments need to be passed: N and start_node. RETURNING. \n");
    return -1;
  }

  // dimension graph
  size_t n = atoi(argv[1]);
  // start node
  size_t start_node = atoi(argv[2]);

  if(start_node >= n){
    printf("The starting node must be between 0 and N-1 RETURNING. \n");
    return -1;
  }

  // Edges matrix
  float** adj = (float**)malloc(sizeof(float*)*n);
  // Cost matrix
  float** cost = (float**)malloc(sizeof(float*)*n);
  // Distance vector from start_node for array impl
  float* dist_array = (float*)malloc(sizeof(float)*n);
  // List of shortest path nodes for array impl
  size_t* pred_array = (size_t*)malloc(sizeof(size_t)*n);
  // Distance vector from start_node for heap impl
  node* dist_heap = (node*)malloc(sizeof(node)*n);
  // List of shortest path nodes for heap impl
  size_t* pred_heap = (size_t*)malloc(sizeof(size_t)*n);

  // allocate edges matrix and populate it
  allocate(adj, n);
  build_problem_instance(adj, n, MAX);

  // Allocate and populate cost matrix
  allocate(cost, n);
  init_cost(cost, adj, n);

  // measure time for array implementation
  for (size_t i = 0; i < REPETITIONS; i++) {
    clock_gettime(CLOCK_REALTIME, &requestStart);
    dijkstra_array(cost, dist_array, pred_array, start_node, n);
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }

  //printf("%lf\t", (accum / REPETITIONS));
  printf("%lu,", n);
  printf("%lf,", (accum / REPETITIONS));

  // measure time for heap implementation
  accum = 0;
  for (size_t i = 0; i < REPETITIONS; i++) {
    clock_gettime(CLOCK_REALTIME, &requestStart);
    dijkstra_heap(cost, dist_heap, pred_heap, start_node, n);
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    accum += (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
  }

  //printf("%lf\t", (accum / REPETITIONS));
  printf("%lf\n", (accum / REPETITIONS));

  // check if the distances are correct
  if (check_dist(dist_array, dist_heap, n) == 1) {
    printf("\ncheck... correct\n");
  }
  else{
    printf("\ncheck... wrong\n");
    //print_vec(dist_array, n);
    //printf("\n");
    //print_heap(dist_heap, n);
  }

  // check paths, useless as for the generated graphs there are multiple equivalet paths
  if (check_pred(pred_array, pred_heap, n) == 1) {
    printf("\ncheck... correct\n");
  }
  else{
    printf("\ncheck... wrong\n");
  }

  free_mat(adj, n);
  free_mat(cost, n);
  free(dist_heap);
  free(dist_array);
  free(pred_array);
  free(pred_heap);


}
