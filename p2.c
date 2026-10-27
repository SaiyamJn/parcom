#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <num_iterations>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        printf("Please enter a positive number of iterations.\n");
        return 1;
    }

    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        #pragma omp for schedule(static, 2)
        for (int i = 0; i < n; i += 2) {
            int end = i + 1;

            if (end >= n)
                end = n - 1;

            printf("Thread %d: Iterations %d -- %d\n",
                   id, i, end);
        }
    }

    return 0;
}

// Compile and run
// gcc -fopenmp omp_chunks.c -o omp_chunks
// export OMP_NUM_THREADS=2
// ./omp_chunks 4
// Sample output
// Thread 0: Iterations 0 -- 1
// Thread 1: Iterations 2 -- 3
// Thread assignment can vary by OpenMP runtime; the example shown is the manual's expected sample.