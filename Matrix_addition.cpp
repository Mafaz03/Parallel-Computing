#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
using namespace std;

double u(double x) {
    return 7 - (x * tan(x));
}

int main() {
    double dx = 0.01;
    double start = -1.0;
    double end = 1.0;
    int N = static_cast<int>((end - start) / dx) + 1;

    vector<double> xvals(N);
    vector<double> uvals(N);
    vector<double> dudx(N);

    for (int i = 0; i < N; i++) {
        xvals[i] = start + i * dx;
        uvals[i] = u(xvals[i]);
    }

    #pragma omp parallel for
    for (int i = 1; i < N-1; i++) {
        dudx[i] = (uvals[i+1] - uvals[i-1]) / (2.0 * dx);
    }

    // First-order at boundaries
    dudx[0] = (uvals[1] - uvals[0]) / dx;
    dudx[N-1] = (uvals[N-1] - uvals[N-2]) / dx;

    // Optionally print results or further processing

    return 0;
}