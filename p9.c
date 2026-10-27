#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
    int rank, size, value;
    int sum, prod, max, min;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    value = rank + 1;
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("=== MPI_Reduce Results (on root only) ===\n");
        printf("SUM = %d\nPROD = %d\nMAX = %d\nMIN = %d\n",
               sum, prod, max, min);
    }
    MPI_Allreduce(&value, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    printf("Process %d: Allreduce Results: SUM=%d, PROD=%d, MAX=%d, MIN=%d\n",
           rank, sum, prod, max, min);
    MPI_Finalize();
    return 0;
}


// Compile and execute
// mpicc -o reduce_allreduce mpi_reduce_allreduce.c
// mpirun -np 4 ./reduce_allreduce 