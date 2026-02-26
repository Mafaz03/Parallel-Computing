#include <iostream>
#include <mpi.h>

int main(int argc, char** argv){
    int a[4] = {10, 20, 30, 40};
    int local_sum = 0;
    int myid, size;
    int sum = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Compute local sum
    for (int i = 0; i < 4; i++){
        a[i] = a[i] * myid;
        local_sum += a[i];
    }

    MPI_Reduce(&local_sum,
               &sum,
               1,
               MPI_INT,
               MPI_SUM,
               0,
               MPI_COMM_WORLD);

    if (myid == 0){
        printf("Rank %d: Global Sum = %d\n", myid, sum);
    }

    MPI_Finalize();
    return 0;
}