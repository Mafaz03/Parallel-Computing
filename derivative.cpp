#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>

using namespace std;


double u(double x){
    const double PI = 3.141592653589793;
    return 7 - (x * tan(x));
}

int main(){
    double dx = 0.01;
    double start = -1.0;
    double end = 1.0;
    int N = ((end - start) / dx) + 1;

    vector<double> xvals(N);
    vector<double> uvals(N);
    vector<double> dudx(N);
    vector<double> dudx_2(N);
    vector<double> dudx_3(N);

    for (int i = 0; i < N; i++) {
        xvals[i] = start + i * dx;
        uvals[i] = u(xvals[i]);
    }

    // second order
    #pragma omp parallel for
    for (int i = 1; i < N-1; i++) {
        dudx_2[i] = (uvals[i+1] - uvals[i-1]) / (2.0 * dx);
    }

    // fourth order
    #pragma omp parallel for
    for (int i = 2; i < N-2; i++) {
        dudx_3[i] = (-uvals[i+2] + 8.0*uvals[i+1] - 8.0*uvals[i-1] + uvals[i-2]) 
                    / (12.0 * dx);
    }

    // First-order at boundaries
    dudx_2[0] = (uvals[1] - uvals[0]) / dx;
    dudx_2[N-1] = (uvals[N-1] - uvals[N-2]) / dx;
    dudx_3[0] = (uvals[1] - uvals[0]) / dx;
    dudx_3[N-1] = (uvals[N-1] - uvals[N-2]) / dx;
    
    for (int i = 1; i < N-1; i++)
        cout << dudx_2[i] << "\n";

    return 0;
}