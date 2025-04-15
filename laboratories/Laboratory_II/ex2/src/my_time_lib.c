#include "../include/my_time_lib.h"

// Put here the implementation of mu_fn and sigma_fn

double mu_fn(double *x, int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += x[i];
    }
    return sum / n;
}

double sigma_fn(double *x, double mu, int n)
{
    double sse = 0.0;
    for (int i = 0; i < n; i++)
        sse += (x[i] - mu) * (x[i] - mu);
    return sse / n;
}

// -------------------------------------------------
