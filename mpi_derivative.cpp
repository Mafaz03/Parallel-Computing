#include <iostream>
#include <mpi.h>
#include <cmath>
#include <fstream>

float f(float x){
    return (x*x*x) - sin(5* x);
}

float f_s(float x){
    return (3*x*x) - 5 * cos(5* x);
}

int main(int argc, char** argv){
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    float bc_0 = f_s(0);
    float bc_3 = f_s(3);

    float delta_x = 0.01;

    int Nx = 3/delta_x;

    float local_derivatives[Nx];
    local_derivatives[0] = bc_0;
    local_derivatives[Nx-1] = bc_3;

    int local_N = Nx / size;
    int start = rank * local_N;
    int end;

    if (rank == size - 1)
        end = Nx;
    else
        end = start + local_N;


    for (int i = start; i < end; i++){
        
        if (i == 0)
            local_derivatives[i - start] = f_s(0); // bc 1
        else if (i == Nx - 1)
            local_derivatives[i - start] = f_s(3); // bc 3
        else {
            float x = i * delta_x;
            local_derivatives[i - start] = (f(x) - f(x-delta_x))/delta_x;
        }
    }

    float derivates[Nx];

    
    MPI_Gather(
            local_derivatives,
            end - start,
            MPI_FLOAT,
            derivates,
            end - start,
            MPI_FLOAT,
            0,
            MPI_COMM_WORLD
        );
    
    
    if (rank == 0){
        std::ofstream file("derivate.dat");
        for (int i = 0; i < Nx; i++){
            printf("%f", derivates[i]);
            float x = i * delta_x;
            printf(" | %f", f_s(x));
            printf(" | %f\n", derivates[i] - f_s(x));
            file << derivates[i] << " " << f_s(x) << "\n";
        }
        file.close();
    }
    MPI_Finalize();
    // return 0;
}