#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "energia.h"

/*COMPILAR
gcc -c -fopenmp energia.c -o energia.o
gcc -c -fopenmp calculo_piOMP.c -o calculo_piOMP.o
gcc energia.o calculo_piOMP.o -fopenmp -lm -o calculo_piOMP
export OMP_NUM_THREADS=4
./calculo_piOMP */

int main(int c, char** argv){
    double tempo_inicio, tempo_fim, tempo;//, energy_total;
	double sum=0, pi=0;
	int i,n;
    double step;

    printf("Introduce the number of iterations n: \n");
    if(c<2)
        scanf("%d", &n);
    else{
        n=atoi(argv[1]);
        printf("%d\n",n);
    }

    step=1.0/((float) n);

	tempo_inicio=omp_get_wtime(); // Iniciar a contagem de tempo	
    if(ENERGIA){
        rapl_init();
        start_rapl_sysfs();
    }


	#pragma omp parallel for reduction (+:sum)//// num_threads(NUM_TH)
	for (i=0;i < n; i++){
		sum += 4.0 / (1.0 + (i + 0.5) * step *(i + 0.5) * step );
		///printf(">>> thread: %d\n", omp_get_thread_num());
	}
    
	pi= step*(sum);
	printf("pi eh %lf\n", pi);

	tempo_fim=omp_get_wtime(); // Finalizar contagem do tempo
    if(ENERGIA){
        double energy = end_rapl_sysfs();
        printf("Energia consumida em Joules:   %.5f\n", energy); // (6) imprimir consumo de energia em Joules
    }
    tempo=tempo_fim-tempo_inicio;

	printf("Tempo: %f\n", tempo);//, energy_total, energy_total/tempo);
	return 0;
}