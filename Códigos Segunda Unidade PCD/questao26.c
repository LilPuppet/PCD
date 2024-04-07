#include <stdio.h>
#include <math.h>
#include <omp.h>
//compilar: gcc -o questao26 questao26.c -fopenmp
//rodar ./questao26

int main() {
    int n = 1000000, minhasthreads = 12;//Tamanho do looping e número de threads
    double resultado1 = 0.0,resultado2 = 0.0, tempoi, tempof;//resultados, tempo inicial e tempo final

    //Teste com um thread
    tempoi = omp_get_wtime();
    #pragma omp parallel for num_threads(1) reduction(+:resultado1)
    for (int i = 0; i < n; i++) {resultado1 += sin(i);}
    tempof = omp_get_wtime();
    printf("Single-thread: %f \n", tempof - tempoi);//usando o tempo de quando começou menos o tempo que terminou, obtemos o tempo real

    //Teste com vários threads
    tempoi = omp_get_wtime();
    #pragma omp parallel for num_threads(minhasthreads) reduction(+:resultado2)
    for (int i = 0; i < n; i++) {resultado2 += sin(i);}
    tempof = omp_get_wtime();
    printf("Multi-thread: %f \n", tempof - tempoi);

    return 0;
}
