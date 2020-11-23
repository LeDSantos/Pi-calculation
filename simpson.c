/*
Pi value calculation using Simpson numerical integration.
Miquel Bernat Laporta i Granados
Mathematics UAB
miquelbernat.laporta@e-campus.uab.cat
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "energia.h" 

//Integrated function
double f(double x){
    return 4/(1+x*x);
}

int main(int c, char** argv){

    int i,n,k,t;
    double a=0;
    double b=1;
    double I;
    double h;
    double temp1=0;
    double temp2=0;
    double temp;
    double *x;

    printf("Introduce the number of nodes:\n");
    if(c<2)
        scanf("%d", &n);
    else{
        n=atoi(argv[1]);
        printf("%d\n",n);
    }
    double begin=omp_get_wtime();

    //clock_t begin = clock();
    h=(b-a)/n;
    x=malloc((n+1)*sizeof(double));
    if( x == NULL ){
        fprintf(stderr,"Memory allocation error...");
        exit(1);
    }else{
        for(i=0; i<=n; i++){
            x[i]=a+i*h;
        }
        for(k=2; k<n; k+=2){
            temp1 += 2*f(x[k]);
        }
        for(t=1; t<n; t++){
            if(t % 2 != 0){
                temp2 += 4*f(x[t]);
            }else{
                temp2 += 0;
            }
        }

        temp = temp1+temp2;

        I=(h/3)*(f(x[0])+temp+f(x[n]));
        //clock_t end = clock();
        double end=omp_get_wtime();
        if(ENERGIA){
            double energy = end_rapl_sysfs();
            printf("Energia consumida em Joules:   %.5f\n", energy); // (6) imprimir consumo de energia em Joules
        }
        printf("Approximated pi value: %.16G\n",I);
        double time_spent = (double)(end - begin);// / CLOCKS_PER_SEC;
        printf("Total execution time: %.15G sec\n", time_spent);
        return 0;
    }
}
