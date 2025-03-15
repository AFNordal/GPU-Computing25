#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 10
#define NINSTANCES 5

// --------------------------------------------------------------------------------

/* Generating vectors with known mean and std
 *
 * The Central Limit Theorem (CLT) states that the sum of a large number of independent, identically distributed
 * random variables tends to follow a normal distribution, regardless of the original distribution.
 * By summing multiple uniform random numbers, we approximate a normal distribution without using complex transformations.
*/

#define N_CLT 12

double generate_random(double mean, double std_dev) {
    double sum = 0.0;
    for (int i = 0; i < N_CLT; i++) {
        sum += (double)rand() / RAND_MAX;
    }
    double normal_approx = (sum - (N_CLT / 2.0)) / sqrt(N_CLT / 12.0);
    return mean + std_dev * normal_approx;
}

// --------------------------------------------------------------------------------
// Functions to compute arithmetic and geometric mean

double arithmetic_mean(double *vector, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += vector[i];
    }
    return sum / size;
}

double geometric_mean(double *vector, int size) {
    double product = 1.0;
    for (int i = 0; i < size; i++) {
        product *= vector[i] > 0 ? vector[i] : 1;
    }
    return pow(product, 1.0 / size);
}

// --------------------------------------------------------------------------------

int main(void) {
    
    // Generate arrays with known mean and standard deviation
    double mu[NINSTANCES] = {5.0, 37.0, 6.0, 4.0, 15.0};
    double sigma[NINSTANCES] = {1.0, 2.0, 3.0, 2.0, 1.0};
    
    srand(time(NULL));
    double vectors[NINSTANCES][SIZE];
    for (int i = 0; i < NINSTANCES; i++) {
        for (int j = 0; j < SIZE; j++) {
            vectors[i][j] = generate_random(mu[i], sigma[i]);
        }
    }

    // Print results as they were produced by real mesurements
    for (int i=0; i<NINSTANCES; i++) {
    	fprintf(stdout, "Instance %d of the problem:\n", i+1);
	for (int j=0; j<SIZE; j++) {
	    fprintf(stdout, "\tTime of cycle %d: %lf\n", j, vectors[i][j]);
	}
	fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
    
    // Compute the instance per instance average
    double instance_arithmetic_mean[NINSTANCES];
    
    for (int i = 0; i < NINSTANCES; i++) {
        double a_mean = arithmetic_mean(vectors[i], SIZE);
        instance_arithmetic_mean[i] = a_mean;
        
        fprintf(stdout, "Vector %d - Arithmetic Mean: %.4f\n", i+1, a_mean);
    }
    fprintf(stdout, "\n");

    // Compute the aggregated results comparing the usage of arithmetic and geometric mean
    double overall_arithmetic_mean = 0.0;
    double overall_geometric_mean = 1.0;

    overall_arithmetic_mean = arithmetic_mean(instance_arithmetic_mean, NINSTANCES);
    overall_geometric_mean  = geometric_mean(instance_arithmetic_mean, NINSTANCES);

    fprintf(stdout, "Overall Arithmetic Mean: %.4f\n", overall_arithmetic_mean);
    fprintf(stdout, "Overall Geometric Mean: %.4f\n", overall_geometric_mean);
    
    return(0);
}

