/*
Pi value calculation using Montecarlo algorithm parallelized with OPENMP library.
Miquel Bernat Laporta i Granados
Mathematics UAB
miquelbernat.laporta@e-campus.uab.cat
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SEED time(NULL)

  double pi(int n){

  srand(SEED);
  int i, count;
  double x,y,z;
  count = 0;

  for(i = 0; i < n; i++){

    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    z = x * x + y * y;
    if( z <= 1) count++;
    printf("Current interation %d with pi value: %lf\n",i,(double)count / (double)n * 4);
  }

  double pi_val = (double)count / (double)n * 4;

  return pi_val;
}

int main(){

  double pi_value;
  int n;
  printf("Introduce the number of iterations n:\n");
  scanf("%d", &n);

  clock_t begin = clock();
  #pragma omp parallel shared(pi_value)
  {
  pi_value = pi(n);
}
  clock_t end = clock();

  printf("Approximate pi value: %.30G\n", pi_value);
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Final execution time: %.15G sec\n", time_spent);
  return 0;
}
