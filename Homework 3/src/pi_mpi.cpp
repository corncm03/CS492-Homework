// File: pi_mpi.cpp
// Version: 1.0
// Description:
// This program calculates an approximate value of PI using MPI.
// I split the loop iterations across all MPI processes using a cyclic
// distribution. That means each process starts at its rank number and
// then skips ahead by the total number of processes.
//
// I chose this approach because each PI calculation loop iteration is
// independent, so the work can be divided without one process depending
// on another during the main calculation.
//
// Each process calculates its own local sum. Then I use MPI_Reduce to
// combine all local sums into one total sum on the master process.
// Only rank 0 prints the final PI value, process count, and execution time
// so the output does not get cluttered.
//
// I used MPI_Wtime() to measure execution time and double values to keep
// the approximation accurate enough for this assignment.



#include <cstdio>
#include <mpi.h>

int main(int argc, char* argv[])
{
    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    int rank, size;

    // Get process ID (rank) and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Required problem size
    const long long N = 100000;

    double step = 1.0 / (double)N;
    double local_sum = 0.0;
    double total_sum = 0.0;
    double pi = 0.0;

    // I start timing using MPI's built-in timer
    double start_time = MPI_Wtime();

    // Each process handles a portion of the loop
    // I am using a cyclic distribution here (i = rank, rank+size, ...)
    for (long long i = rank; i < N; i += size)
    {
        double x = (i + 0.5) * step;
        local_sum += 4.0 / (1.0 + x * x);
    }

    // Combine all local sums into total_sum on rank 0
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Only the master process calculates and prints the result
    if (rank == 0)
    {
        pi = step * total_sum;

        double end_time = MPI_Wtime();
        double elapsed_time = end_time - start_time;

        printf("MPI PI Calculation\n");
        printf("------------------\n");
        printf("N = %lld\n", N);
        printf("Processes = %d\n", size);
        printf("Approximate PI = %.15f\n", pi);
        printf("Execution Time = %.10f seconds\n", elapsed_time);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}