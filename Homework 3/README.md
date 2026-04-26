# CS492 – Homework 03

## PI Calculation using Serial, MPI, and OpenMP

### Overview

For this assignment, I implemented three versions of a program that calculates the value of π (pi):

* Serial version (CPU only)
* MPI version (distributed memory)
* OpenMP version (shared memory)

I chose to use a simple numerical integration method because each iteration is independent, which makes it easy to parallelize.

---

### Algorithm Used

I used the rectangle (midpoint) method to approximate π:

pi ≈ ∑ (4 / (1 + x²)) * step

Where:

* step = 1.0 / N
* x = (i + 0.5) * step

I chose this because it is simple and works well for demonstrating parallelism since each loop iteration does not depend on others.

---

### File Structure

HW03_PI/
├── src/
│   ├── pi_serial.cpp
│   ├── pi_mpi.cpp
│   └── pi_openmp.cpp
├── results/
│   ├── screenshots/
│   └── timing_data.txt
├── bin/
├── README.md
└── .gitignore

---

### Compilation Instructions

#### Serial Version

g++ src/pi_serial.cpp -o bin/pi_serial

#### MPI Version

mpic++ src/pi_mpi.cpp -o bin/pi_mpi

#### OpenMP Version

g++ -fopenmp src/pi_openmp.cpp -o bin/pi_openmp

---

### Execution Instructions

#### Serial

./bin/pi_serial

#### MPI (example with 8 processes)

mpirun -np 8 ./bin/pi_mpi

#### OpenMP (example with 8 threads)

export OMP_NUM_THREADS=8
./bin/pi_openmp

---

### Test Configuration

The assignment requires:

* N = 100,000
* MPI Processes / OpenMP Threads:

  * 8
  * 10
  * 16
  * 32

I used the same value of N for all implementations to keep the comparison fair.

---

### Performance Measurement

Each version measures execution time using built-in timing functions:

* Serial: standard timing (chrono or similar)
* MPI: MPI_Wtime()
* OpenMP: omp_get_wtime()

I recorded the execution times for each run and saved them in:

results/timing_data.txt

---

### Speedup Calculation

Speedup is calculated as:

Speedup = Serial Time / Parallel Time

I used this to compare how much faster the MPI and OpenMP versions performed compared to the serial version.

---

### Notes / Observations

* The serial version is the slowest since it runs everything on one core.
* MPI distributes work across processes, which improves performance.
* OpenMP uses threads, which is simpler to implement but depends on shared memory.
* Increasing threads/processes generally improves performance, but not always perfectly due to overhead.

---

### What I Learned

I learned how to:

* Break a problem into parallel tasks
* Use MPI for distributed systems
* Use OpenMP for shared memory parallelism
* Measure and compare performance between different implementations

I also saw that just adding more threads does not always mean better performance, which helped me understand overhead and efficiency better.

---
