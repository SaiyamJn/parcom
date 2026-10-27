#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
    int rank,size,number;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(size<2) {
        if(rank==0) printf("This program requires at least two processes.\\n");
        MPI_Finalize();
        return 0;
    }
    if(rank==0) {
        number=123;
        MPI_Send(&number,1,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("Process 0 sent number %d to process 1\\n",number);
    } else if(rank==1) {
        MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Process 1 received number %d from process 0\\n",number);
    }
    MPI_Finalize();
    return 0;
}

// Compile and run
// mpicc -o mpi_send_recv mpi_send_recv.c
// mpirun -np 2 ./mpi_send_recv
// Sample output
// Process 0 sent number 123 to process 1
// Process 1 received number 123 from process 0
// Run with at least two MPI processes. The two output lines may appear in either order.