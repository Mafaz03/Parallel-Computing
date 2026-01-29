#include <iostream>
#include <cmath>


double f(double x){
    return std::sin(x) / (2.0 * std::pow(x, 3));
}

int main(){

    const double EXACT = 0.198557;
    double a = 1.00;
    double b = std::acos(-1.0); // pi

    int n = 32;
    double h = (b - a) / n;

    double summation = 0.0;
    for (int i = 1; i < n; i++){
        double x = a + i * h;
        summation += f(x);
    }

    double result = h * ((f(a)/2) + summation + (f(b)/2));
    std::cout << "result: " << result << std::endl;
    std::cout << "error: " << result - EXACT << std::endl;
    return 0;
}