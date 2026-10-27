#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
    int rank, size;
    int a[100], b[10], c[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 10) {
        MPI_Finalize();
        return 0;
    }
    if (rank == 0) {
        for (int i = 0; i < 100; i++)
            a[i] = i + 1;
        printf("Root process initialized array to scatter.\n");
    }
    MPI_Scatter(a, 10, MPI_INT, b, 10, MPI_INT,
                0, MPI_COMM_WORLD);
    printf("Process %d received data: ", rank);
    for (int i = 0; i < 10; i++) {
        printf("%d ", b[i]);
        b[i] = b[i] * 2;
    }
    printf("\n");
    MPI_Gather(b, 10, MPI_INT, c, 10, MPI_INT,
               0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Root process gathered modified data:\n");
        for (int i = 0; i < 100; i++) {
            printf("%d ", c[i]);
            if ((i + 1) % 10 == 0)
                printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}

// Compile and execute
// mpicc -o scatter_gather mpi_scatter_gather.c
// mpirun -np 10 ./scatter_gather