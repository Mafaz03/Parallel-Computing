/* Hello world program using OpenMP */
#include <stdio.h>
#include <omp.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
int main()
{

  int nthreads = 0;
  vector<string> dict;

  printf("\nAbout to enter the parallel world...");
  printf("\n");

  int thread_count = omp_get_max_threads();
  dict.resize(thread_count);      

  #pragma omp parallel num_threads(thread_count)
  {
      int id = omp_get_thread_num();
      dict[id] = "Hello world from thread number " + std::to_string(id);
      printf("rank: %d\n", id);
  }

  printf("Entered the serial world...\n");

  for (int i = 0; i < thread_count; i++){
    cout << dict[i] << endl;
  }

  return 0;
}
