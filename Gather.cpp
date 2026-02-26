#include <iostream>
#include <mpi.h>

int main(int argc, char** argv){
    int a[6] = {10};
    int all_sum[6];
    int myid, size;
    // int sum = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // // Compute local sum
    // for (int i = 0; i < 4; i++){
    //     a[i] = a[i] * myid;
    //     local_sum += a[i];
    // }
    a[0] = a[0] * myid;
    MPI_Gather(a,
               1,
               MPI_INT,
               all_sum,
               1,
               MPI_INT,
               0,
               MPI_COMM_WORLD);

    // if (myid == 0){
    if (myid == 0){
            for(int i = 0; i < size; i++){
                printf("From rank %d: %d\n", i, all_sum[i]);
            }
            // delete[] all_sums;
        }
    // }

    MPI_Finalize();
    return 0;
}