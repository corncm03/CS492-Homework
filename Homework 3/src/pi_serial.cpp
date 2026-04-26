
// File: pi_serial.cpp
// Version: 1.0
//Description:
// This program calculates an approximate value of PI using a serial
// loop. I am using the midpoint rectangle method because each loop
// iteration can be handled independently later when I move this to
// MPI and OpenMP.
//
// This version runs completely serial and is used as the baseline
// for comparing performance with MPI and OpenMP implementations.


#include <cstdio>
#include <chrono>

int main()
{
    // I am using the required N value from the assignment.
    const long long N = 100000;

    double step = 1.0 / (double)N;
    double sum = 0.0;
    double pi = 0.0;

    // I start timing right before the main calculation.
    auto start_time = std::chrono::high_resolution_clock::now();

    // This is the serial part of the program.
    // Each i value calculates one small piece of the total area.
    for (long long i = 0; i < N; i++)
    {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    // I stop timing right after the calculation is finished.
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_time = end_time - start_time;

    printf("Serial PI Calculation\n");
    printf("---------------------\n");
    printf("N = %lld\n", N);
    printf("Approximate PI = %.15f\n", pi);
    printf("Execution Time = %.10f seconds\n", elapsed_time.count());

    return 0;
}