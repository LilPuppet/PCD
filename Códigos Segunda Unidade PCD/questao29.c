#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementação simples de strtok_r
// O objetivo é processar um conjunto de linhas de texto, dividindo-as em tokens
// usando espaços, tabulações e quebras de linha como delimitadores.
//paralelizado, cada thread faz uma linha.
char *my_strtok_r(char *str, const char *delim, char **saveptr) {
    if (str == NULL) {
        str = *saveptr;
    }
    // Se a string de entrada for NULL, tenta continuar a tokenização a partir do último ponto
    // Isso permite que a função seja chamada repetidamente para obter tokens subsequentes.
    if (str == NULL) {
        return NULL;
    }
    // Se a string de entrada ainda for NULL após a tentativa de continuar, retorna NULL
    // Isso indica que não há mais tokens para serem extraídos.

    char *token_start = str; // Encontra o início do próximo token na string de entrada
    char *token_end = strpbrk(token_start, delim); // Usa strpbrk para encontrar o primeiro caractere que é um delimitador

    if (token_end == NULL) {// Se não houver mais delimitadores na string, retorna o token restante
        *saveptr = NULL;
        return token_start;
    }

    *token_end = '\0';// Atualiza o ponteiro de salvamento para apontar para o próximo caractere após o delimitador
    *saveptr = token_end + 1;

    return token_start;
}

int main() {
    char str[] = "Hello, World! How are you?";
    char *saveptr;
    char *token = my_strtok_r(str, " ", &saveptr);

    while (token != NULL) {
        printf("%s\n", token);
        token = my_strtok_r(NULL, " ", &saveptr);
    }

    return 0;
}
