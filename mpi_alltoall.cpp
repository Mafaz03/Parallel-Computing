#include <iostream>
#include <mpi.h>

int main(int argc, char** argv){

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sendbuf[size];
    int recvbuf[size];

    for (int i = 0; i < size; i++){
        sendbuf[i] = rank * 10 + i;
    }

    MPI_Alltoall(
        sendbuf,   
        1,         
        MPI_INT,
        recvbuf,   
        1,         
        MPI_INT,
        MPI_COMM_WORLD
    );

    printf("Rank %d received: ", rank);
    for (int i = 0; i < size; i++){
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}