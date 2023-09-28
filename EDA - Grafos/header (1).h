#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N_NOS 8

typedef struct no No;
typedef struct grafo Grafo;

No *montaNo(char letra, int peso, No *prox);
Grafo *montaGrafo(int nos, No **viz);
int *dist_curta(Grafo *g, char nome);
void busca_profundidade(Grafo*g, char ini);

struct no {
  char letra;
  int peso;
  No *prox;
};

struct grafo {
  int nos;
  int *visitados;
  No **viz;
};