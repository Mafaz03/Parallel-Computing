#include <iostream>
#include <mpi.h>

struct new_dt{
    double a[3] = {12.67, 56.45, 25.32};
    double b[2] = {56.79, 98.26};
    int n = 10;
};

int main(int argc, char** argv){

    MPI_Init(&argc, &argv);
    int myid, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    struct new_dt dummy_dt;
    
    // 1
    int lengths[3] = { 3, 2, 1};

    // 2
    MPI_Aint displacements[3];
    MPI_Aint base_address;
    MPI_Get_address(&dummy_dt, &base_address);
    MPI_Get_address(&dummy_dt.a, &displacements[0]);
    MPI_Get_address(&dummy_dt.b, &displacements[1]);
    MPI_Get_address(&dummy_dt.n, &displacements[2]);

    displacements[0] = MPI_Aint_diff(displacements[0], base_address);
    displacements[1] = MPI_Aint_diff(displacements[1], base_address);
    displacements[2] = MPI_Aint_diff(displacements[2], base_address);
    
    // 3
    MPI_Datatype types[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT};

    MPI_Datatype dummy_dt_type;
    MPI_Type_create_struct(3, lengths, displacements, types, &dummy_dt_type);
    MPI_Type_commit(&dummy_dt_type);

    // broadcast
    MPI_Bcast(
        &dummy_dt, 
        1, 
        dummy_dt_type,
        0, 
        MPI_COMM_WORLD
    );
    for (int j = 0; j<size; j++){
        if (myid == j){
            printf("myid: %d\na: ", j);
            for (int i = 0; i<3; i++){
                printf("%f ", dummy_dt.a[i]);
            }
            printf("\nb: ");
            for (int i = 0; i<2; i++){
                printf("%f ", dummy_dt.b[i]);
            }
            printf("\nn: %d", dummy_dt.n);
        }
    }


    MPI_Finalize();
    
    return 0;
}