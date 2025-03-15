#include <string.h>


#define EX2_SOLUTION {                          \
    int i, k;                                   \
    double T;					\
    len = 1;                                    \
    for(i=0; i<n; i++) len *= 2;                \
    printf("Vectors len in %d\n", len);         \
    a = (dtype*)malloc(sizeof(dtype)*len);      \
    b = (dtype*)malloc(sizeof(dtype)*len);      \
    c = (dtype*)malloc(sizeof(dtype)*len);      \
    time_t t;                                   \
    srand((unsigned) time(&t));                 \
    int typ = (strcmp( XSTR(dtype) ,"int")==0); \
    if (typ) {                                  \
        int rand_range = (1<<11);               \
        printf("rand_range= %d\n", rand_range); \
        for (i=0; i<len; i++) {                 \
            a[i] = rand()/(rand_range);         \
            b[i] = rand()/(rand_range);         \
        }                                       \
    } else {                                    \
        for (i=0; i<len; i++) {                 \
        a[i] = (dtype)rand()/((dtype)RAND_MAX); \
        b[i] = (dtype)rand()/((dtype)RAND_MAX); \
        }                                       \
    }                                           \
						\
    TIMER_DEF(0);				\
    fprintf(stdout,"\nComputation start...\n");	\
	for (k=-2; k<NITER; k++) {		\
		TIMER_START(0);			\
		for (i=0; i<len; i++) {		\
			c[i] = a[i] + b[i];	\
		}				\
		TIMER_STOP(0);			\
		T = TIMER_ELAPSED(0) / 1.e6;	\
		printf("Iter %d took %lfs\n",	\
			k, T);			\
		if( k >= 0) times[k]=T;		\
    }						\
    printf("Computation performed!\n\n");	\
}
