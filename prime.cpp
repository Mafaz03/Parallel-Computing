#include <iostream>
#include <vector>

using namespace std;

int main(){

    int n = 1000;
    
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;

    #pragma omp parallel for num_threads(8)
    for (int i = 2; i < n; i++){
        if (isPrime[i] == true){
            // unmark all its multipliers
            for (int j = i*i; j <= n; j += i){
                isPrime[j] = false;
            }
        }
    }

    for (int i = 0; i < n; i++){
        if (isPrime[i]){
            std::cout << i << " ";
        }
    }


    return 0;
}