#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main(){

    // initialising matrix
    int r, c;

    r = 5;
    c = 2;

    vector<int> A(r*c);
    vector<int> B(r*c);
    vector<int> C(r*c);
    // vector<vector<int>> A(r, vector<int>(c));
    // vector<vector<int>> B(r, vector<int>(c));
    // vector<vector<int>> C(r, vector<int>(c, 0));

    for (int i = 0; i < (r*c); i++){
        A[i] = 1;
        B[i] = 1;
        C[i] = 0;
    }


    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < (r*c); i++){
        C[i] = A[i] + B[i];
    }

    for (int i = 0; i < (r*c); i++){
        if (i%c == 0){
            std::cout << std::endl;
        }  
        std::cout << C[i] << " ";   
        // std::cout << i << " ";   
    }


    return 0;
}