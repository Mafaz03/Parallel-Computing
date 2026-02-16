#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

double func(int i, int j){
    return i*j*0.3;
}

int main() {
    int num_threads = 8;
    int rows = 20;
    int cols = 20;

    vector<vector<double>> matrix1(rows, vector<double>(cols));
    vector<vector<double>> matrix2(rows, vector<double>(cols));
    vector<vector<double>> matrix3(rows, vector<double>(cols));

    // Input matrix1
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] = func(i, j);
        }
    }

    // Input matrix2
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix2[i][j] = func(i, j);
        }
    }
    // adding
    double wtime = omp_get_wtime();
    #pragma omp parallel for num_threads(num_threads) default(none) shared(matrix1, matrix2, matrix3, rows, cols) collapse(2)
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrix3[i][j] = 0.0;
            for (int k = 0; k < cols; k++){
                matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    wtime = omp_get_wtime() - wtime;
    printf("Time taken is %f\n", wtime);

    // cout << "Summation:\n";
    
    // for (int i = 0; i < rows; i++){
    //     for (int j = 0; j < cols; j++){
    //         cout << matrix3[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    

    return 0;
}