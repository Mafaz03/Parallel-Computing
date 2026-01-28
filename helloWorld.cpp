#include <iostream>
#include <omp.h>

using namespace std;

void Hello(){
     printf("Done from thread: %d out of: %d\n", omp_get_thread_num(), omp_get_num_threads());
}

int main(int argc, const char * argv[]){
    int n = 4; // default 
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    cout << "Using " << n << " threads" << endl;
    omp_set_num_threads(n);
    #pragma omp parallel
    {
        Hello();
    }
    return 0;
}