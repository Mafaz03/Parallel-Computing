#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>

double f(double x){
    return std::sin(x) / (2.0 * std::pow(x, 3));
}

int main(){
    
    int n = 32;
    const double EXACT = 0.198557;
    double a = 1.00;
    double b = std::acos(-1.0); // pi
    double h = (b - a) / n;

    double sum_1 = 0.0, sum_2 = 0.0;

    #pragma omp parallel for reduction(+:sum_1) num_threads(4)
    for (int i = 1; i < n; i += 2){
        double x = a + i * h;
        sum_1 += f(x);
    }

    #pragma omp parallel for reduction(+:sum_2) num_threads(4)
    for (int i = 2; i < n; i += 2){
        double x = a + i * h;
        sum_2 += f(x);
    }

    double result = (h/3) * (f(a) + f(b) + 4*sum_1 + 2*sum_2);
    std::cout << "result: " << result << std::endl;
    std::cout << "error: " << result - EXACT << std::endl;
    return 0;

}