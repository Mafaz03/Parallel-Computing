#include <iostream>
#include <mpi.h>

int main(int argc, char** argv){
    int a[6] = {10, 20, 30, 40, 50, 60};
    int myid, size;
    int sum = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(&a,
               1,
               MPI_INT,
               &sum,
               1,
               MPI_INT,
               0,
               MPI_COMM_WORLD);

    // if (myid == 0){
    printf("Rank %d: val = %d\n", myid, sum);
    // }

    MPI_Finalize();
    return 0;
}