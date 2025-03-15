#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define dtype int
#define NITER 10

#include "include/my_time_lib.h"

// -------- uncomment these seven lines when solutions are published --------
#include "solutions/get_time_test_solutions.c"
#define RESULTS
#ifdef RESULTS
#include "solutions/my_time_lib_solution.c"
    MU_SOL
    SIGMA_SOL
#endif
// ------------------------------------------------------------------------

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s n\n", argv[0]);
        return(1);
    }

    printf("argv[0] = %s\n", argv[1]);

    int n = atoi(argv[1]), len;
    dtype *a, *b, *c;
    double times[NITER];

    printf("n = %d\n", n);
    printf("dtype = %s\n", XSTR(dtype));

    /* Generate now two vectors a and b of size (2^n) and fill them with random integers
     *  in the range [-(2^11), (2^11)]. After this, compute the vector sum c = a + b (for
     *  all i in [0, (2^n)-1] c[i] = a[i] + b[i]).
     *
     * Other tasks:
     *      1) Record CPU time on time[] vector. Compute theri mean and standard deviation.
     *           You can use the macro difined into "include/my_time_lib.h".
     *      2) change now the dtype form 'int' to 'double' and observe how the computation time changes
     *
     * NOTE:
     * for random generation of integers in [-(2^11), (2^11)] use: "rand()/(1<<11)"
     * for random generation of doubles use: "(double)rand()/((double)RAND_MAX)"
     */

#ifdef RESULTS
    EX2_SOLUTION
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */



#endif

    /*  Here we compute the vectors' mean and variance; these functions must be implemented inside
     *   of the library "src/my_time_lib.c" (and their headers in "include/my_time_lib.h").
     *
     * Given a vector v := [v_1, ... v_n] his mean mu(v) is defined as: (v_1 + ... + v_n)/n
     *   his variance sigma(v) as: ( (v_1 - mu(v))^2 + ... + (v_n - mu(v))^2 ) / (n)
     */
    double mu = 0.0, sigma = 0.0;

#ifdef RESULTS
    mu = mu_fn_sol(times, NITER);
    sigma = sigma_fn_sol(times, mu, NITER);
#else
        /* |========================================| */
        /* |           Put here your code           | */
        /* |========================================| */

#endif

    printf(" %10s | %10s | %10s |\n", "v name", "mu(v)", "sigma(v)");
    printf(" %10s | %10f | %10f |\n", "time", mu, sigma);

    return(0);
}
