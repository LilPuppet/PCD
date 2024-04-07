#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
/*
compilar: gcc -g -Wall -fopenmp -o questao23 questao23.c
executar: ./questao23 <numero_de_threads> <tamanho_do_vetor>
 */

void Print_iters(int iterations[], long n);

int main(int argc, char *argv[])
{
    omp_sched_t sched;
    int num_threads, chunksize;
    int tamanho, i;
    num_threads = strtol(argv[1], NULL, 10);
    tamanho = strtol(argv[2], NULL, 10);
    int *iterations;
    iterations = (int *)malloc((tamanho + 1) * sizeof(int));
    omp_get_schedule(&sched, &chunksize);
#pragma omp parallel num_threads(num_threads)

#pragma omp for schedule(guided)
    for (i = 0; i < tamanho; i++)
    {
        iterations[i] = omp_get_thread_num();
    }

    printf("\nEscalonamento: %i \n", sched);
    printf("Chunksize: %i \n", chunksize);
    Print_iters(iterations, tamanho);
    free(iterations);
}

void Print_iters(int iterations[], long n)
{
    int i, start_iter, stop_iter, which_thread;

    printf("\n");
    printf("Thread\t\tIteracoes\n");
    printf("------\t\t----------\n");
    which_thread = iterations[0];
    start_iter = stop_iter = 0;
    for (i = 0; i <= n; i++)
        if (iterations[i] == which_thread)
            stop_iter = i;
        else
        {
            printf("%4d  \t\t%d -- %d\n", which_thread, start_iter,
                   stop_iter);
            which_thread = iterations[i];
            start_iter = stop_iter = i;
        }
    printf("%4d  \t\t%d -- %d\n", which_thread, start_iter,
           stop_iter);
}