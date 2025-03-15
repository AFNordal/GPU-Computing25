#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define dtype int
#define NITER 10

#include "include/my_time_lib.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s n\n", argv[0]);
        return(1);
    }

    printf("argv[0] = %s\n", argv[1]);

    int i;
    TIMER_DEF(0);
    dtype *a, *b, c;
    double times[NITER];
    double mu = 0.0, sigma = 0.0;
    int n = atoi(argv[1]), len = 1;
    for(i=0; i<n; i++) len *= 2;

    fprintf(stdout, "dtype = %s\n", XSTR(dtype));
    fprintf(stdout, "n = %d, len = %d\n", n, len);

    fprintf(stdout, "Allocating memory... ");
    fflush(stdout);
    TIMER_START(0);

    a = (dtype*)malloc(sizeof(dtype)*len);
    b = (dtype*)malloc(sizeof(dtype)*len);

    TIMER_STOP(0);
    fprintf(stdout, "done in %lfs\n", TIMER_ELAPSED(0) / 1.e6);

    fprintf(stdout, "Generating input vectors... ");
    fflush(stdout);

    time_t t;
    TIMER_START(0);
    srand((unsigned) time(&t));
    int typ = (strcmp( XSTR(dtype) ,"int")==0);
    if (typ) {
        int rand_range = (1<<11);
        for (i=0; i<len; i++) {
		a[i] = rand()/(rand_range);
		b[i] = rand()/(rand_range);
        }
    } else {
        for (i=0; i<len; i++) {
		a[i] = (dtype)rand()/((dtype)RAND_MAX);
		b[i] = (dtype)rand()/((dtype)RAND_MAX);
        }
    }
    TIMER_STOP(0);
    fprintf(stdout, "done in %lfs\n", TIMER_ELAPSED(0) / 1.e6);

    fprintf(stdout, "\n\nPerforming scalar product...\n");
    fflush(stdout);

    for (int k=-2; k<NITER; k++) {
	TIMER_START(0);
        c = 0.0;
	for (i=0; i<len; i++) c += a[i] * b[i];
        TIMER_STOP(0);
                
	double iter_time = TIMER_ELAPSED(0) / 1.e6;
	if( k >= 0) times[k] = iter_time;

        printf("Iteration %d tooks %lfs\n", k, iter_time);
    }
    fprintf(stdout, "%d iterations performed\n\n", NITER);

    mu = mu_fn_sol(times, NITER);
    sigma = sigma_fn_sol(times, mu, NITER);

    printf(" %10s | %10s | %10s |\n", "v name", "mu(v)", "sigma(v)");
    printf(" %10s | %10f | %10f |\n", "time", mu, sigma);

    int nflop = 2*len - 1;
    fprintf(stdout, "\nEach scalar produce required 2*len -1 = %d floating point operations.\n", nflop);

    double flops = nflop / mu;
    fprintf(stdout, "The scalar product acheved %lf MFLOP/s\n", flops / 1.e6);

    return(0);
}
