// File: pi_openmp.cpp
// Version: 1.0
// Description:
// This program calculates an approximate value of PI using OpenMP.
// I used a parallel for loop to split the loop iterations across threads.
//
// Each thread computes part of the sum, and I use reduction so each thread
// has a private copy of the sum variable. OpenMP then combines all of the
// partial sums safely at the end.
//
// I chose reduction instead of critical or atomic because it avoids
// forcing threads to wait every time they update the sum.
//
// I also used omp_get_wtime() to measure execution time

#include <cstdio>
#include <omp.h>

int main()
{
    // I am using the required N value from the assignment.
    const long long N = 100000;

    double step = 1.0 / (double)N;
    double sum = 0.0;
    double pi = 0.0;

    // I start timing right before the parallel work begins.
    double start_time = omp_get_wtime();

    // I use reduction here so each thread gets its own private sum.
    // OpenMP combines all of the private sums safely at the end.
    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (long long i = 0; i < N; i++)
    {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    // I stop timing after the final PI value has been calculated.
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    printf("OpenMP PI Calculation\n");
    printf("---------------------\n");
    printf("N = %lld\n", N);
    printf("Threads = %d\n", omp_get_max_threads());
    printf("Approximate PI = %.15f\n", pi);
    printf("Execution Time = %.10f seconds\n", elapsed_time);

    return 0;
}