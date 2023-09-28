#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1031

// 1031 porquê é um número maior que 1024 e é primo

#define CONT 1000

char* lista[MAX];

unsigned long hash(char* str);
int duplo_hash(char* str);
void hash_insere(char* nome, char** s);
int busca_hash(char* nome, char** s);
void remove_hash(char* nome, char** s);

int colisao = 0;

int main(void) {
    for (int n = 0; n < MAX; n++) {
        lista[n] = malloc(sizeof(char));
        *lista[n] = 'x';
    }
    int n = 0;
    char placa[8];
    double total_t;

    FILE* f = fopen("arq.txt", "r");
    if (!f) {
        fprintf(stderr, "erro ao ler o arquivo");
        exit(2);
    }

    clock_t inicio_t = clock();
    printf("Tempo iniciado:%ld\n", inicio_t);
    while (n < CONT && !feof(f)) {
        fscanf(f, "%[^\n]\n", placa);
        printf("%s", placa);
        printf(" %d\n", hash(placa));

        hash_insere(placa, lista);
        n++;
    }

    putchar('\n');
    clock_t fim_t = clock();
    printf("Tempo final:%ld\n\n", fim_t);
    total_t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    printf("Colisões: %d\n", colisao);
    printf("Tempo Total: %f\n\n", total_t);

    printf("Tempo de pesquisa de objetos da lista:\n\n");
    inicio_t = clock();

    printf("Tempo iniciado:%ld\n\n", inicio_t);
    int busca = busca_hash("CNF4901", lista);
    if (busca == -1) {
        printf("Placa nao esta na lista");
    }
    else {
        printf("Placa: %s\nIndice: %d\n", lista[busca], busca);
    }
    busca = busca_hash("DDV3460", lista);
    if (busca == -1) {
        printf("Placa nao esta na lista");
    }
    else {
        printf("Placa: %s\nIndice: %d\n", lista[busca], busca);
    }
    busca = busca_hash("ZRH7222", lista);
    if (busca == -1) {
        printf("Placa nao esta na lista");
    }
    else {
        printf("Placa: %s\nIndice: %d\n", lista[busca], busca);
    }
    putchar('\n');

    fim_t = clock();
    printf("Tempo final:%ld\n\n", fim_t);
    total_t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    printf("Tempo Total: %f\n\n", total_t);

    printf("Tempo de remocao de objetos:\n\n");
    inicio_t = clock();

    printf("Tempo iniciado:%ld\n\n", inicio_t);

    remove_hash("CNF4901", lista);
    remove_hash("DDV3460", lista);
    remove_hash("ZRH7222", lista);

    putchar('\n');
    fim_t = clock();
    printf("Tempo final:%ld\n\n", fim_t);
    total_t = (double)(fim_t - inicio_t) / CLOCKS_PER_SEC;
    printf("Tempo Total: %f\n\n", total_t);

    for (int i = 0; i < MAX ; i++) {
        free(lista[i]);
    }
    return 0;
}

unsigned long hash(char* str) {
    unsigned long hash = 5381;
    int c = *str;
    while (c) {
        hash = ((hash << 5) + hash) + c;
        c = *str++;
    }
    return hash % MAX;
}

int duplo_hash(char* str) {
    unsigned long i = hash(str);
    unsigned long j = 21 - (i % 21);
    return (i + j) % MAX;
}

void hash_insere(char* nome, char** s) {
    int indice = hash(nome);
    int alter = duplo_hash(nome);
    while (*s[indice] != 'x') {
        colisao++;
        indice = (indice + alter) % MAX;
    }
    s[indice] = malloc(sizeof(char*) * strlen(nome) + 1);
    strcpy(s[indice], nome);
    return;
}

int busca_hash(char* nome, char** s) {
    int i = hash(nome);
    int cont = 0;
    int alter = duplo_hash(nome);
    while (lista[i] != NULL && cont < colisao) {
        if (strcmp(s[i], nome) == 0) {
            return i;
        }
        i = (i + alter) % MAX;
        cont++;
    }
    return -1;
}

void remove_hash(char* nome, char** s) {
    int indice = busca_hash(nome, s);
    if (indice == -1) {
        printf("Placa nao esta na lista\n");
        return;
    }
    else {
        *s[indice] = 'x';
        printf("Placa %s removida da posicao %d\n", nome, indice);
        return;
    }
}
