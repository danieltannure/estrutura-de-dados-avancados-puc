#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int main(void) {
    int min = 1;
    int max = 20;
    int cont = 10;
    int lista[] = { 0,0,0,0,0,0,0,0,0,0 };
    Arvore* raiz;
    int i = 0;

    srand(time(0));

    printf("Numeros gerados: ");
    while (i < cont) {
        int num = (rand() % (min - max + 1)) + min;
        int checa = mesmo_n(num, lista);
        if (checa == 1) {
            lista[i] = num;
            printf("%d ", num);
            i++;
        }
    }

    putchar('\n');

    raiz = cria_arv(
        lista[0],
        cria_arv(lista[1],
            cria_arv(lista[3], cria_arv(lista[7], NULL, NULL),
                cria_arv(lista[8], NULL, NULL)),
            cria_arv(lista[4], cria_arv(lista[9], NULL, NULL), NULL)),
        cria_arv(lista[2], cria_arv(lista[5], NULL, NULL),
            cria_arv(lista[6], NULL, NULL)));

    Arvore* raiz_abb = NULL;

    for (int i = 0; i < cont; i++) {
        raiz_abb = insere_bb(raiz_abb, lista[i]);
    }

    int verifica;

    exibe_pre(raiz);
    exibe_pre(raiz_abb);
    verifica = checa_abb(raiz);
    if (verifica == 1) {
        printf("Nao e uma arvore binaria de busca\n");
    }

    verifica = checa_abb(raiz_abb);
    if (verifica == 0) {
        printf("Esta e uma arvore binaria de busca\n");
    }

    printf("A altura da arvore binaria com elementos inseridos por nivel e: %d\n", altura_a(raiz));

    printf("A altura da arvore binaria de busca e: %d\n", altura_a(raiz_abb));

    raiz = rotaciona_a(raiz);
    exibe_pre(raiz);
    raiz_abb = rotaciona_a(raiz_abb);
    exibe_pre(raiz_abb);
    
    return 0;
}

