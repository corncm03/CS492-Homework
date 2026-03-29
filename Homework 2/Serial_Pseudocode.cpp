// This gives me access to std::cin and std::cout so I can read input
// from the keyboard and print the final result to the screen.
#include <iostream>

// Main function: this is where the program starts running.
int main()
{
    // N stores how many terms of the Leibniz series I want to use.
    // A larger N should usually give me a better approximation of pi.
    int N;

    // sum stores the running total as each term is added or subtracted.
    // This is the main value that builds toward the final approximation.
    double sum = 0.0;

    // piApprox stores the final answer after the series is finished.
    double piApprox = 0.0;

    // Ask the user for the number of terms to use in the calculation.
    // This controls how many times the loop will run.
    std::cout << "Enter the number of terms: ";

    // Read the user input and store it in N so the program knows
    // how many terms it should process.
    std::cin >> N;

    // Loop through every term in the Leibniz series starting at 0 and stopping at N - 1.
    // This is where the actual approximation work happens one term at a time.
    for (int i = 0; i < N; i++)
    {
        // term stores the current fraction for this loop iteration
        // before I add it into the running total.
        double term;

        // If i is even, this term should be positive.
        // That matches the alternating pattern of the Leibniz series.
        if (i % 2 == 0)
        {
            // Compute the positive fraction for this position in the series.
            // The denominator follows the odd-number pattern: 1, 3, 5, 7, ...
            term = 1.0 / (2 * i + 1);
        }
        else
        {
            // If i is odd, this term should be negative.
            // This is what makes the series alternate between adding and subtracting.
            term = -1.0 / (2 * i + 1);
        }

        // Add the current term into sum so the total keeps building each pass.
        // If I were checking the math step by step, this is the value that should change every iteration.
        sum = sum + term;
    }

    // Multiply the finished sum by 4 because the Leibniz series gives pi / 4.
    // This converts the running total into the actual approximation of pi.
    piApprox = 4.0 * sum;

    // Print the final approximation so I can see the result and verify
    // that the program produced a value close to 3.14 when N is large enough.
    std::cout << "Approximate value of pi: " << piApprox << '\n';

    // Return 0 to show the program finished normally.
    return 0;
}
