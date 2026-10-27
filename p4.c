#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
int prime(int n) {
    if(n<2) return 0;
    for(int i=2;i<=sqrt(n);i++)
        if(n%i==0) return 0;
    return 1;
}
int main(int argc, char *argv[]) {
    if(argc!=2) {
        printf("Usage: %s <n>\\n",argv[0]);
        return 1;
    }
    int n=atoi(argv[1]), serial=0, parallel=0;
    double t=omp_get_wtime();
    for(int i=1;i<=n;i++) if(prime(i)) serial++;
    printf("\\nSerial Time : %f seconds\\n",omp_get_wtime()-t);
    t=omp_get_wtime();
    #pragma omp parallel for reduction(+:parallel)
    for(int i=1;i<=n;i++) if(prime(i)) parallel++;
    printf("Parallel Time : %f seconds\\n",omp_get_wtime()-t);
    printf("\\nNumber of primes found: %d\\n",serial);
    printf("First 10 primes (serial): ");
    int count=0;
    for(int i=2;i<=n && count<10;i++)
        if(prime(i)) { printf("%d ",i); count++; }
    printf("\\n");
    return 0;
}





// Compile and run
// gcc -fopenmp omp_primes.c -o omp_primes -lm
// export OMP_NUM_THREADS=4
// ./omp_primes 100000
// Sample output
// Serial Time : (varies) seconds
// Parallel Time : (varies) seconds
// Number of primes found: 9592
// First 10 primes (serial): 2 3 5 7 11 13 17 19 23 29
// Count and first 10 primes match the manual for n=100000. Timings vary.