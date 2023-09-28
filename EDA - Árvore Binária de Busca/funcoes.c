#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

Arvore* cria_arv(int x, Arvore* esq, Arvore* dir) {
    Arvore* no = (Arvore*)malloc(sizeof(Arvore));
    no->info = x;
    no->esq = esq;
    no->dir = dir;
    return no;
}

Arvore* insere_bb(Arvore* p, int x) {
    if (!p) {
        Arvore* no = (Arvore*)malloc(sizeof(Arvore));
        no->info = x;
        no->esq = NULL;
        no->dir = NULL;
        p = no;
    }
    else if (x < p->info) {
        p->esq = insere_bb(p->esq, x);
    }
    else if (x > p->info) {
        p->dir = insere_bb(p->dir, x);
    }
    return p;
}

void exibe_pre(Arvore* p) {
    if (!p) {
        printf("*\n\n");

        return;
    }
    printf("chave: %d,filho esquerdo: %p,filho direito: %p\n\n", p->info, p->esq,
        p->dir);
    exibe_pre(p->esq);
    exibe_pre(p->dir);
    return;
}

int mesmo_n(int n, int* list) {
    int len_l = 10;
    for (int i = 0; i < len_l; i++) {
        if (list[i] == n) {
            return 0;
        }
    }
    return 1;
}

int checa_abb(Arvore* p) {
    Arvore* dir = p->dir;
    Arvore* esq = p->esq;
    int n;

    if (dir != NULL) {
        if (dir->info < p->info) {
            return 1;
        }
        else {
            n = checa_abb(p->dir);
            if (n == 1) {
                return 1;
            }
        }
    }
    else if (esq != NULL) {
        if (esq->info > p->info) {
            return 1;
        }
        else {
            n = checa_abb(p->esq);
            if (n == 1) {
                return 1;
            }
        }
    }
    return 0;
}
int max(int a,int b){
  if(a>b){
    return a;
  }
  return b;
}
int altura_a(Arvore* p) {
    if (!p->dir && !p->esq) {
        return 1;
    }
    else if (!p->dir) {
        return 1 + altura_a(p->esq);
    }
    else if (!p->esq) {
        return 1 + altura_a(p->dir);
    }
    return 1 + max(altura_a(p->esq), altura_a(p->dir));
}

    Arvore* rotaciona_a(Arvore * p){
        if (p) {
            Arvore* guarda = p->dir;
            if (!p->dir && !p->esq) {
                return p;
            }
            p->dir = p->esq;
            p->esq = guarda;
            rotaciona_a(p->dir);
            rotaciona_a(p->esq);
        }
        return p;
    }