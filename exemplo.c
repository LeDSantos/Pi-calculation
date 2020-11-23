/*
* EXEMPLO: Multiplicação de matriz medindo consumo de energia e tempo de execução
*
* Arquivo com exemplo de como utilizar a biblioteca para ler consumo de energia.
*
* COMO COMPILAR usando a lib para ler consumo de energia:  
* $ gcc exemplo.c energia.c -o mmatriz
* onde:
*   "exemplo.c" é o arquivo da sua aplicação
*   "energia.c" é o arquivo com o código da lib do RAPL (deve estar no mesmo diretório)
*   "mmatriz" é o nome do arquivo executável de saida
*
* Obs. IMPORTANTE: os contadores de energia não tem precisão para execuções com tempo menor que 0.001 segundos. 
*/

/* (1) Incluir Header file para ter acesso as funções para ter o consumo de energia */
#include "energia.h" 

void initialize_matrices();
void multiply_matrices();

int main(int argc, char* argv[])
{
    /* (2) chamar esta funcao no inicio do main para inicializar a lib do RAPL */
    rapl_init();
	
    initialize_matrices();
    
	start_rapl_sysfs(); // (3) Iniciar a contagem de consumo de energia
    clock_t t = clock(); // Iniciar a contagem de tempo
        /* (4) Chamar aqui a função que faz o que você deseja medir o tempo e a energia */
        multiply_matrices();
        /*************************************************/
    t = clock() - t; // Finalizar contagem do tempo
    double energy = end_rapl_sysfs();   // (5) Finalizar a contagem dos contadores de energia
    double tempo = ((double)t)/CLOCKS_PER_SEC; // transforma tempo para segundos
    printf("Tempo de execucao em segundos: %.5f\n", tempo);
    printf("Energia consumida em Joules:   %.5f\n", energy); // (6) imprimir consumo de energia em Joules
    
	return 0;
}

/*
* Naive matrix multiplication
* Author:  P.J. Drongowski
* Date:    10 June 2013
* Copyright (c) 2013 Paul J. Drongowski
*/

#define MSIZE     500
float matrix_a[MSIZE][MSIZE] ;
float matrix_b[MSIZE][MSIZE] ;
float matrix_r[MSIZE][MSIZE] ;

void initialize_matrices(){
    int i, j ;
    int n = MSIZE;
	{
        for (i = 0 ; i < MSIZE ; i++) {
            for (j = 0 ; j < MSIZE ; j++) {
                matrix_a[i][j] = (float) rand() / RAND_MAX ;
                matrix_b[i][j] = (float) rand() / RAND_MAX ;
                matrix_r[i][j] = 0.0 ;
            }
        }
    }
}

void multiply_matrices(){
    int i, j, k ;
    int n = MSIZE;
	{
        for (i = 0 ; i < MSIZE ; i++) {
            for (j = 0 ; j < MSIZE ; j++) {
                float sum = 0.0 ;
                for (k = 0 ; k < MSIZE ; k++) {
                    sum = sum + (matrix_a[i][k] * matrix_b[k][j]) ;
                }
                matrix_r[i][j] = sum ;
            }
        }
    }
}
