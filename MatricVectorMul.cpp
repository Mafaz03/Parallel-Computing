#include <iostream>
#include <mpi.h>

int main(int argc, char** argv){
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int vector[3] = {1, 2, 3};

    int myid, size, local_sum = 0;
    int b[3];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < 3; i++){
        local_sum += matrix[myid][i] * vector[i];
    }

    MPI_Gather(
            &local_sum,
            1,
            MPI_INT,
            b,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD
        );

    if (myid == 0){
        for(int i = 0; i < 3; i++){
            printf("%d\n", b[i]);
        }
    }
    MPI_Finalize();
    return 0;

}
