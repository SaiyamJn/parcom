#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
long long fib(int n) {
    if(n<=1) return n;
    long long x,y;
    #pragma omp task shared(x)
    x=fib(n-1);
    #pragma omp task shared(y)
    y=fib(n-2);
    #pragma omp taskwait
    return x+y;
}
int main(int argc, char *argv[]) {
    if(argc!=2) {
        printf("Usage: %s <n_terms>\\n",argv[0]);
        return 1;
    }
    int n=atoi(argv[1]);
    printf("Fibonacci series up to %d terms:\\n",n);
    #pragma omp parallel
    {
        #pragma omp single
        for(int i=0;i<n;i++)
            printf("Fib(%d) = %lld\\n",i,fib(i));
    }
    return 0;
}


// Compile and run
// gcc -fopenmp omp_fib_tasks.c -o omp_fib_tasks
// export OMP_NUM_THREADS=4
// ./omp_fib_tasks 10
// Sample output
// Fibonacci series up to 10 terms:
// Fib(0) = 0
// Fib(1) = 1
// Fib(2) = 1
// Fib(3) = 2
// Fib(4) = 3
// Fib(5) = 5
// Fib(6) = 8
// Fib(7) = 13
// Fib(8) = 21
// Fib(9) = 34
// Prints the first n Fibonacci terms. Output format matches the lab manual.