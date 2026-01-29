/* A little more sophisticated version of hello world */
#include<stdio.h>
#include<stdlib.h>
#include <bits/stdc++.h>
#ifdef _OPENMP
#include<omp.h>

#endif
using namespace std;
std::string Hello(void){
  #ifdef _OPENMP
      int my_rank = omp_get_thread_num();
      int thread_count = omp_get_num_threads();
  #else
      int my_rank = 0;
      int thread_count = 1;
  #endif
  printf("rank: %d\n", my_rank);
      return "Hello from thread " + std::to_string(my_rank) +
            " out of total threads " + std::to_string(thread_count);
  }

int main(int argc, char* argv[])
{
  int thread_count = 1;

  if (argc == 2)
    {
      thread_count = strtol(argv[1], NULL, 10);
    }
  else
    {
      printf("\n A command line argument other than name of the executable is required...exiting the program..\n");
      return 1;
    }
  
  unordered_map<int, string> dict;
  #pragma omp parallel num_threads(thread_count)
  {
    int id = omp_get_thread_num();
    dict[id] = Hello();
  }

  int nthreads = omp_get_max_threads();
  for (int i = 0; i < nthreads; i++){
    cout << dict[i] << endl;
  }

  cout << dict;

  return 0;
}
