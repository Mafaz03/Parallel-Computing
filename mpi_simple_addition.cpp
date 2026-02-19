#include <iostream>
#include <mpi.h>

double f(double x){
    return x*x;
}

int main(int argc, char** argv){
    int myid, size;
    int tag = 100;

    double a = 0.0;
    double b = 1.0;
    int n = 10;
    double h = (b - a) / n;

    double result = 0.0;
    double summation[n];

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    for (int i = 0; i < n; i++)
    {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;
        summation[i] = 0.5 * (f(x1) + f(x2)) * h;
    }

    if (myid != 0 ) // not the 'main branch'
    {
        MPI_Send(summation, n, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    }
    else if (myid == 0)
    {
        double recv_buffer[n];
        MPI_Status status;
        MPI_Recv(recv_buffer, n, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, &status);

        for (int j = 0; j < n; j++){
            result += recv_buffer[j];
        }
        printf("Integral result: %f\n", result);
    }

    MPI_Finalize();

    return 0;
}