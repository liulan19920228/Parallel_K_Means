#include <stdio.h>
#include <stdlib.h>
#include "seq_kmeans.c"
#include "kmeans.h"

void random_data(float ** array, int m, int n) {
    for(int i=0; i<m ; i++) {
        for(int j=0; j<n; j++){
            array[i][j] = (float)rand()/(float)RAND_MAX;
        }
    }
}

int main()
{
    int     K = 128, D = 1000, N = 12800;
    float   threshold = 0.001;
    int    *membership;
    float **data;
    float **center;
    double  timing, sequential_timing, cuda_timing;
    int     num_iterations;
    
    printf("numofdatas       = %d\n", N);
    printf("dimension     = %d\n", D);
    printf("numClusters   = %d\n", K);
    printf("threshold     = %.4f\n", threshold);
    
    malloc2D(data, N,D, float);
    random_data(data, N, D);
    membership = (int*) malloc(N * sizeof(int));
    
    timing            = wtime();
    sequential_timing = timing;
    
    /* start the timer for the core computation -----------------------------*/
    /*clusters = seq_kmeans(data, dimension, numObjs, numClusters, threshold,membership, &num_iterations);
    timing            = wtime();
    sequential_timing = timing - sequential_timing;
    printf("Seq Computation timing = %10.4f sec\n", sequential_timing);
    printf("Loop iterations    = %d\n", num_iterations);*/
    
    free(membership);
    membership = (int*) malloc(N * sizeof(int));
    timing      = wtime();
    cuda_timing = timing;
    clusters = cuda_kmeans(data, D, N, K, threshold,membership, &num_iterations);
    timing      = wtime();
    cuda_timing = timing - cuda_timing;
    
    printf("Cuda Computation timing = %10.4f sec\n", cuda_timing);
    printf("Loop iterations    = %d\n", num_iterations);
    //printf("speed up = %.4f\n", sequantial_timing/cuda_timing);
    
    free(membership);
    free(center[0]);
    free(center);
    free(data[0]);
    free(data);
    return(0);
}
