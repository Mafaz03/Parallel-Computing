#include <iostream>
#include <cmath>
#include<mpi.h> 

double f(double x){
    return std::sin(x) / (2.0 * std::pow(x, 3));
}

int main(int argc, char** argv){
    int i, myid, size, tag=100;
    double result = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    const double EXACT = 0.198557;
    double a = 1.00;
    double b = std::acos(-1.0); // pi

    int n = 32;
    double summation[n];
    double h = (b - a) / n;

    for (int i = 0; i < n; i++)
    {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;
        summation[i] = 0.5 * (f(x1) + f(x2)) * h;
    }

    if (myid != 0 )
        MPI_Send(summation, n, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    else if (myid == 0)
    {
        double recv_buffer[n];
        MPI_Status status;
        MPI_Recv(recv_buffer, n, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, &status);
        
        for (int j = 0; j < n; j++){
            result += recv_buffer[j];
        }
    }
    MPI_Finalize();

    std::cout << "result: " << result << std::endl;
    std::cout << "error: " << result - EXACT << std::endl;
    return 0;
}