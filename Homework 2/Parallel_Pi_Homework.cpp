// This gives me access to input and output so rank 0 can read N
// and print the final approximation after the parallel work is finished.
#include <iostream>

// This lets me control the number of decimal places shown in the output.
#include <iomanip>

// This gives me access to the MPI functions used to start MPI,
// identify ranks, share N, and combine the partial sums.
#include <mpi.h>
 
// I am using the standard namespace here so I do not need to write std:: every time.
using namespace std;
 
// Main function: this is where the MPI version of the program starts.
int main(int argc, char* argv[]) {
    // rank tells me which process I am, and size tells me
    // how many total MPI processes are running.
    int rank, size;

    // N stores the total number of terms in the Leibniz series.
    long long N;

    // start and end define the section of the series this rank is responsible for.
    // chunk stores the base number of terms assigned to each process.
    long long start, end, chunk;

    // localSum stores this rank's partial result.
    // globalSum stores the combined result after MPI_Reduce runs on rank 0.
    double localSum = 0.0, globalSum = 0.0;

    // term stores the current fraction for the loop iteration on this rank.
    double term;
 
    // Initialize MPI before using any MPI functions.
    // None of the rank or communication calls should happen before this point.
    MPI_Init(&argc, &argv);

    // Get this process rank so each copy of the program knows which process it is.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes so I know how the work is being divided.
    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
    // Rank 0 acts as the master process here.
    // I only want one rank reading from the keyboard, so rank 0 handles the input.
    if (rank == 0) {
        // Ask for N so the whole MPI program knows how many total terms to process.
        cout << "Enter N: ";

        // Read the input into N on the master process.
        cin >> N;
    }
 
    // Send N from rank 0 to every process so all ranks use the same problem size.
    // If this works, every process should agree on the same value of N.
    MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
 
    // Compute the base chunk size for each process.
    // This divides the work as evenly as possible, and the last rank takes any leftover terms.
    chunk = N / size;
    start = rank * chunk;
    end = (rank == size - 1) ? N : start + chunk;
 
    // Loop only over the range assigned to this rank.
    // This is where the parallel version splits the series across processes.
    for (long long i = start; i < end; i++) {
        // Even values of i produce positive terms and odd values produce negative terms.
        // This keeps the same math as the serial version while only processing part of the range here.
        term = ((i % 2 == 0) ? 1.0 : -1.0) / (2.0 * i + 1.0);

        // Add this term into the local partial sum for this rank.
        // If the work split is correct, each rank should build only its own piece of the series.
        localSum += term;
    }
 
    // Combine all local sums into one global sum on rank 0.
    // If this reduction works, rank 0 should end up with the same total sum
    // the serial version would have before multiplying by 4.
    MPI_Reduce(&localSum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
 
    // Only rank 0 has the full reduced result, so only rank 0 prints the final answer.
    if (rank == 0) {
        // Multiply by 4 to convert the Leibniz sum into the approximation of pi.
        double piApprox = 4.0 * globalSum;

        // Print with fixed precision so the result is easier to read and compare.
        cout << fixed << setprecision(10);

        // Show the final approximation.
        // If everything is working, this should be close to the serial result for the same N.
        cout << "Approximate value of pi = " << piApprox << endl;
    }
 
    // Shut down MPI now that the communication and output are finished.
    MPI_Finalize();

    // Return 0 to show the program finished normally.
    return 0;
}
