/*
    File: pi_mpi.cpp
    Version: 1.0

    CS492 - Homework Assignment 03

    This program calculates an approximate value of PI using MPI.
    I split the total number of iterations across all processes.
    Each process computes its own local sum, and then I combine
    the results using MPI_Reduce.

    I chose this approach because the PI calculation loop has no
    dependencies between iterations, so it is easy to divide the work.

    Compile:
        mpic++ src/pi_mpi.cpp -o bin/pi_mpi

    Run (example with 8 processes):
        mpirun -np 8 ./bin/pi_mpi
*/

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