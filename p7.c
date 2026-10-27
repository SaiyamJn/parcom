#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
    int rank, data = 42;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
        printf("Process 0 is broadcasting data = %d\n", data);
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d received data = %d\n", rank, data);
    MPI_Finalize();
    return 0;
}

// Compile and execute
// mpicc -o mpi_broadcast mpi_broadcast.c
// mpirun -np 4 ./mpi_broadcast
