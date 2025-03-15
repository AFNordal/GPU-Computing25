# Laboratory II

## Exercise 1

You have to follow the directives written in 'laboratories/Laboratory_II/ex1/stack_n_heap.c' by putting your solution code inside the macro with "Put here your code". This exercise has eight small subproblems involving an elementwise sum between stack/heap vectors or matrices. For each subproblem, compute the elapsed CPU time by using the variables ('temp_1', 'temp_2') and storing the result in 'CPU_times\[subproblem_id\]'.

First step: check that by running 'make' and './bin/stack_n_heap' the program will return you:

	You are now running YOUR CODE:
	Problem 0 runs in 0.00000000 CPU time
	Problem 1 runs in 0.00000000 CPU time
	Problem 2 runs in 0.00000000 CPU time
	Problem 3 runs in 0.00000000 CPU time
	Problem 4 runs in 0.00000000 CPU time
	Problem 5 runs in 0.00000000 CPU time
	Problem 6 runs in 0.00000000 CPU time
	Problem 7 runs in 0.00000000 CPU time

Start then to write your code.

When the solution will be published, you only need to uncomment lines 30 and 31 for running them.

## Exercise 2

Given a command-line parameter n, write a program that generates two random vectors a and b of length 2^n and compute their sum c = a + b. Benchmark its runtime by performing two warm-up cycles and averaging over 10 rounds. The main function must look like the following:

```C
int main(void) {
    [ … ]
    for(i = -WARM_UP; i<NITER; i++) {
        [ … timer start … ]
        c = add (a,b);
        [ … timer stop … ]
        if (i>0)
            mesures[i] = [ … time_stop – time_start … ];
    }
    [ … compute mean and std … ]
    return 0;
}
```

You can find a template code inside "ex2/". Keep all the benchmark function into the library "ex2/src/my_time_lib.c" and "ex2/include/my_time_lib.h". Compleate the provided Makefile and use the provided sbatch script.


## Exercise 3

Given two random vectors of the same size 2n, compute their scalar product: <a, b> = \sum_{k=1}^{2^n} a_i * b_i.

Get the execution time and FLOP/s. How match operations do a scalar produce require?

## Exercise 4

Generate three different vectors with different mean 𝜇 and standard deviation 𝜎. Compute the overall average with both arithmetic and geometric mean.

## Exercise 5

Benchmark a program that use OpenBLAS to perform a general matrix multiplication between two random square matrices. Get the execution time and the FLOP/s.

Implement your own general matrix multiplication and compare your performance with the OpenBLAS implementation.

## Exercise 6

Generate a dense 𝑛×𝑚 matrix where each entry has a probability 𝑝 of being 0.

Write two functions: 
1. Convert a dense matrix to COO format.
2. Convert a COO matrix to dense format.

Benchmark both functions for different values of 𝑝 and aggregate the results using the geometric mean.

