#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include <time.h>

#include "include/my_time_lib.h"

#define dtype double
#define WARMUP 2
#define NITER 10

// Function to fill a pre-allocated matrix with random values
void fill_matrix(int rows, int cols, dtype *matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i*cols +j] = (float)(rand() % 100) / 10.0;
        }
    }
}

void init_matrix(int rows, int cols, dtype *matrix, dtype val) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i*cols +j] = val;
        }
    }
}

void my_gemm(int n, int k, int m, dtype *A, dtype *B, dtype *C) {

    for (int i=0; i<n; i++)
	for (int j=0; j<m; j++)
	    for (int h=0; h<k; h++)
		C[i*m +j] += A[i*k +h] * B[h*m +j];
}


int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Usage: %s n k m\n\nWhere:\tmatrix A has size nxk\n\tmatrix B has size kxm\n\tresult matrix C has size nxm\n\n", argv[0], argv[1], argv[2], argv[3]);
        return(1);
    }
    
    // Generate random matrices
    dtype *A, *B, *C;
    double timers[NITER];
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int m = atoi(argv[3]);
    fprintf(stdout, "Input sizes are %d x %d x %d\n", n, k, m);

    A = (dtype*)malloc(sizeof(dtype)*n*k);
    B = (dtype*)malloc(sizeof(dtype)*k*m);
    C = (dtype*)malloc(sizeof(dtype)*n*m);

    srand(time(NULL));
    fill_matrix(n, k, A);
    fill_matrix(k, m, B);
    init_matrix(n, m, C, 0.0);


    TIMER_DEF(0);
    for (int i=-WARMUP; i<NITER; i++) {

    	// Perform C = A * B using BLAS
	TIMER_START(0);
    	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, 1.0, A, k, B, n, 0.0, C, n);
	TIMER_STOP(0);

	double iter_time = TIMER_ELAPSED(0) / 1.e6;
        if( i >= 0) timers[i] = iter_time;

        printf("Iteration %d tooks %lfs\n", i, iter_time);
	init_matrix(n, m, C, 0.0);
    }


    
    double a_mean = arithmetic_mean(timers, NITER);
    fprintf(stdout, "Arithmetic Mean: %lf\n", a_mean);

    int nflop = n * k * m;
    fprintf(stdout, "\nEach gemm required n*k*m = %d floating point operations.\n", nflop);

    double flops = nflop / a_mean;
    fprintf(stdout, "The OpenBLAS gemm acheved %lf MFLOP/s\n", flops / 1.e6);

    fprintf(stdout, "\nMy GEMM implementation:\n");
    for (int i=-WARMUP; i<NITER; i++) {

        // Perform C = A * B using BLAS
        TIMER_START(0);
	my_gemm(n, k, m, A, B, C);        
        TIMER_STOP(0);

        double iter_time = TIMER_ELAPSED(0) / 1.e6;
        if( i >= 0) timers[i] = iter_time;

        printf("Iteration %d tooks %lfs\n", i, iter_time);
        init_matrix(n, m, C, 0.0);
    }

    a_mean = arithmetic_mean(timers, NITER);
    flops = nflop / a_mean;
    fprintf(stdout, "My GEMM implementation acheved %lf MFLOP/s\n", flops / 1.e6);

    return(0);
}

