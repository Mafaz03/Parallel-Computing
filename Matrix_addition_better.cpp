#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    int num_threads = 10;
    int rows = 200;
    int cols = 200;

    vector<vector<double>> matrix1(rows, vector<double>(cols));
    vector<vector<double>> matrix2(rows, vector<double>(cols));
    vector<vector<double>> matrix3(rows, vector<double>(cols));

    // Input matrix1
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] = 5.43;
        }
    }

    // Input matrix2
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix2[i][j] = 5.24;
        }
    }

    // adding
    double wtime = omp_get_wtime();
    #pragma omp parallel for num_threads(num_threads) default(none) shared(matrix1, matrix2, matrix3, rows, cols) collapse(2)
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    wtime = omp_get_wtime() - wtime;
    printf( "Time taken by thread %d is %f\n", omp_get_thread_num(), wtime );

    // cout << "Summation:\n";
    
    // for (int i = 0; i < rows; i++){
    //     for (int j = 0; j < cols; j++){
    //         cout << matrix3[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    

    return 0;
}