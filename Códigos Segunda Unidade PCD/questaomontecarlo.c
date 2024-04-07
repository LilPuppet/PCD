#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long long int num_lancamentos;
    long long int qtd_no_circulo = 0;
    double estimativa_de_pi;
    printf("Digite o número total de lançamentos: ");
    scanf("%lld", &num_lancamentos);

// Loop paralelo para gerar lançamentos e contar quantos caem dentro do círculo
    #pragma omp parallel for reduction(+:qtd_no_circulo)
    for (long long int lancamento = 0; lancamento < num_lancamentos; lancamento++) {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0; // Gera um número aleatório entre -1 e 1
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0; // Gera um número aleatório entre -1 e 1
        double distancia_quadrada = x * x + y * y; // Calcula a distância quadrada do ponto (x, y) até a origem
        if (distancia_quadrada <= 1) qtd_no_circulo++; // Se a distância quadrada for menor ou igual a 1, o ponto está dentro do círculo
    }
    // Estima Pi usando a proporção de pontos dentro do círculo
    estimativa_de_pi = 4.0 * qtd_no_circulo / (double)num_lancamentos;
    printf("Estimativa de Pi: %lf\n", estimativa_de_pi);

    return 0;
}
