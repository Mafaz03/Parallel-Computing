#include <iostream>
#include <mpi.h>
#include <cmath>
#include <fstream>

int main(int argc, char** argv){

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int to_split[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int disp[5] = {0, 2, 4, 6, 8};
    int sendcounts[5] = {2, 2, 2, 2, 1};
    int each_proc_buf[2] = {-1, -1};

    
    MPI_Scatterv(
        to_split,
        sendcounts,
        disp,
        MPI_INT,
        each_proc_buf,
        sendcounts[rank],
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );
    
    printf("rank: %d\n", rank);
    for (int i = 0; i < 2; i++){
        printf("%d | ", each_proc_buf[i]);
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}