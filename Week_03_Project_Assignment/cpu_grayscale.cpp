// File: cpu_grayscale.cpp
// Version: 1.0
// Description:
//   This is our basic CPU version of grayscale conversion.
//   We made this first so we can verify correctness before moving to CUDA.

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// We are using this struct to group RGB values together for each pixel.
struct Pixel {
    int r;
    int g;
    int b;
};

// We created this function to convert one pixel to grayscale.
int convertToGray(const Pixel& p) {

    // We use the standard grayscale formula from our problem statement
    // because it is simple and widely used.
    double gray = 0.299 * p.r + 0.587 * p.g + 0.114 * p.b;

    // Here we convert to int because grayscale pixel values are whole numbers
    return (int)gray;
}

int main() {

    // We created a small test dataset so that we can easily verify correctness
    vector<Pixel> pixels = {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 255, 255},
        {0, 0, 0}
    };

    vector<int> grayValues(pixels.size());

    // We start the timing before the loop begins
    auto start = chrono::high_resolution_clock::now();

    // This is where we process each pixel one at a time (sequential execution)
    for (int i = 0; i < pixels.size(); i++) {
        grayValues[i] = convertToGray(pixels[i]);
    }

    // Here is where we stop timing after the loop finishes
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = end - start;

    // This is where the program prints results so the team can verify correctness
    cout << "Grayscale Results:" << endl;
    for (int i = 0; i < pixels.size(); i++) {
        cout << "Pixel " << i << " -> " << grayValues[i] << endl;
    }

    // This is where the program prints execution time for the CPU version
    cout << "CPU Execution Time: " << duration.count() << " ms" << endl;

    return 0;
}
