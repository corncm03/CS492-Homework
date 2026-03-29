// This gives me access to input and output so I can read N
// and print the final approximation of pi.
#include <iostream>

// This lets me control how many digits are printed in the final answer.
#include <iomanip>
 
// I am using the standard namespace here so I do not need to write std:: every time.
using namespace std;
 
// Main function: this is where the serial program starts.
int main() {
    // N stores how many total terms I want to use in the Leibniz series.
    // A larger N should usually give me a better approximation of pi.
    long long N;

    // sum stores the running total of all terms in the series.
    double sum = 0.0;

    // term stores the current fraction being added or subtracted in the loop.
    double term;

    // piApprox stores the final approximation after the loop is done.
    double piApprox;
 
    // Ask the user for N so the program knows how many terms to calculate.
    cout << "Enter N: ";

    // Read the user input and store it in N.
    cin >> N;
 
    // Loop through every term from 0 up to N - 1.
    // This is where the serial version does all of the work one term at a time.
    for (long long i = 0; i < N; i++) {
        // Even values of i produce positive terms and odd values produce negative terms.
        // Writing it this way is easier to follow than using pow(-1.0, i),
        // and it lets me verify the sign pattern directly from the code.
        term = ((i % 2 == 0) ? 1.0 : -1.0) / (2.0 * i + 1.0);

        // Add the current term into the running total.
        // If I traced this by hand, sum should keep changing every pass through the loop.
        sum += term;
    }
 
    // Multiply the finished sum by 4 because the Leibniz series computes pi / 4.
    piApprox = 4.0 * sum;
 
    // Print the result with a fixed number of decimal places
    // so the output is easier to read and compare.
    cout << fixed << setprecision(10);

    // Show the final approximation.
    // If N is large enough, I should see a value close to 3.1415926535.
    cout << "Approximate value of pi = " << piApprox << endl;
 
    // Return 0 to show the program finished normally.
    return 0;
}
 
