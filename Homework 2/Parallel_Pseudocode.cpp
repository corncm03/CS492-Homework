// This gives me access to std::cin and std::cout so I can read input
// and print the final result from the master process.
#include <iostream>

// This gives me access to the MPI functions used to start MPI,
// identify each process, send shared values, and combine results.
#include <mpi.h>

// Main function: this is where the parallel program starts.
// argc and argv are passed into MPI_Init in case MPI needs runtime arguments.
int main(int argc, char* argv[])
{
    // rank tells me which process I am.
    // size tells me how many total MPI processes are running.
    int rank, size;

    // N stores how many total terms should be used in the Leibniz series.
    int N;

    // partialSum stores the local work done by this process only.
    // totalSum will hold the combined result after all processes are reduced together.
    double partialSum = 0.0;
    double totalSum = 0.0;

    // piApprox stores the final approximation of pi after the reduction is complete.
    double piApprox = 0.0;

    // Initialize MPI before using any MPI functions.
    // This is what allows all processes to begin participating in the program.
    MPI_Init(&argc, &argv);

    // Get this process rank so each copy of the program knows which process it is.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes so I know how the work is being divided.
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Rank 0 acts as the master process here.
    // I only ask for input once so every process does not try to read from the keyboard.
    if (rank == 0)
    {
        // Ask the user for the number of terms to use in the approximation.
        // This controls how many total terms the MPI program will process.
        std::cout << "Enter the number of terms: ";
        std::cin >> N;
    }

    // Send N from the master to every process so all ranks use the same problem size.
    // If this step works correctly, every process should loop over the same overall range.
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process works on part of the series instead of every process doing all the work.
    // Starting at i = rank and stepping by size spreads the terms across all ranks.
    for (int i = rank; i < N; i += size)
    {
        // term stores the current fraction for this process at this iteration.
        double term;

        // Even values of i produce positive terms in the Leibniz series.
        if (i % 2 == 0)
        {
            term = 1.0 / (2 * i + 1);
        }
        else
        {
            // Odd values of i produce negative terms.
            term = -1.0 / (2 * i + 1);
        }

        // Add this term into the local partial sum for the current rank.
        // This lets each process build only its own piece of the final answer.
        partialSum = partialSum + term;
    }

    // Combine all partial sums into totalSum on rank 0.
    // If the reduction works, rank 0 should end up with the same overall sum
    // the serial version would get before multiplying by 4.
    MPI_Reduce(&partialSum, &totalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Only the master process has the full reduced result, so only rank 0 prints the answer.
    if (rank == 0)
    {
        // Multiply by 4 because the Leibniz series computes pi / 4.
        piApprox = 4.0 * totalSum;

        // Print the final approximation so I can verify the parallel version
        // is producing a value close to 3.14 when N is large enough.
        std::cout << "Approximate value of pi: " << piApprox << '\n';
    }

    // Shut down MPI now that all parallel work and output are finished.
    MPI_Finalize();

    // Return 0 to show the program finished normally.
    return 0;
}
