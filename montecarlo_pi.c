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

#include "energia.h" 

#define SEED time(NULL)

double pi(int n){

  srand(SEED);
  int i, count;
  double x,y;//,z;
  count = 0;

  #pragma omp parallel for private(x,y) reduction (+:count)
  for(i = 0; i < n; i++){

    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    //z = x * x + y * y;
    //if( x * x + y * y <= 1) count+=1;
    count+=( x * x + y * y <= 1);
    //printf("Current interation %d with pi value: %lf\n",i,(double)count / (double)n * 4);
  }

  double pi_val = (double)count / (double)n * 4;

  return pi_val;
}

int main(int c, char** argv){

  //#pragma omp parallel
  //{
  //  printf("teste\n");
  //}
  //return 0;

  double pi_value;
  int n;
  printf("Introduce the number of iterations n: \n");
  if(c<2)
    scanf("%d", &n);
  else{
    n=atoi(argv[1]);
    printf("%d\n",n);
  }

  if(ENERGIA){
    rapl_init();
    start_rapl_sysfs();
  }
  //clock_t begin = clock();
  double begin=omp_get_wtime();
  pi_value = pi(n);
  //}
  //clock_t end = clock();
  double end=omp_get_wtime();
  if(ENERGIA){
    double energy = end_rapl_sysfs();
    printf("Energia consumida em Joules:   %.5f\n", energy); // (6) imprimir consumo de energia em Joules
  }
  printf("Approximate pi value: %.30G\n", pi_value);
  double time_spent = (double)(end - begin);// / CLOCKS_PER_SEC;
  printf("Final execution time: %.15G sec\n", time_spent);
  return 0;
}
