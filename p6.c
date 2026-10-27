#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
    int rank, data = 10;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
    }
    MPI_Finalize();
    return 0;
}

// Compile and execute
// mpicc -o deadlock deadlock_example.c
// mpirun -np 2 ./deadlock





#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
    int rank, data = 10;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    printf("Process %d completed communication safely.\n", rank);
    MPI_Finalize();
    return 0;
}
// Compile and execute
// mpicc -o no_deadlock deadlock_avoided.c
// mpirun -np 2 ./no_deadlock