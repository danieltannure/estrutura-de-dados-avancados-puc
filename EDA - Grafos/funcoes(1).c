#include "header.h"

No *montaNo(char letra, int peso, No *prox) {
  No *verticeViz = (No *)malloc(sizeof(No));
  verticeViz->letra = letra;
  verticeViz->peso = peso;
  verticeViz->prox = prox;
  return verticeViz;
}

Grafo *montaGrafo(int nos, No **viz) {
  Grafo *gr = (Grafo *)malloc(sizeof(Grafo));
  gr->nos = nos;
  gr->visitados = (int *)malloc(sizeof(int) * nos);
  gr->viz = (No **)malloc(sizeof(No *) * nos);
  for (int i = 0; i < nos; i++) {
    gr->visitados[i] = 0;
    gr->viz[i] = viz[i];
  }
  return gr;
}

int *dist_curta(Grafo *g, char nome) {
  int *menor_dist = (int *)malloc(sizeof(int) * g->nos);
  for (int i = 0; i < g->nos; i++) {
    menor_dist[i] = 0;
  }
  No* p=g->viz[nome%65];
  while(p!=NULL){
    menor_dist[p->letra%65]=p->peso;
    p=p->prox;
  }
  g->visitados[nome%65]=1;
  int caminho=0;
  int cont=2; //ja leu o nó A todo e o G não é legivel
  while(cont<g->nos){
    for(int i=0;i<g->nos;i++){
        if(menor_dist[i]!=0 && g->visitados[i]==0){
          caminho=menor_dist[i];
          p=g->viz[i];
        }
      while(p!=NULL){
        if(menor_dist[p->letra%65]==0 && g->visitados[p->letra%65]==0){
          menor_dist[p->letra%65]= p->peso+caminho;
        }
        else if(menor_dist[p->letra%65]>p->peso+caminho){
          menor_dist[p->letra%65]= p->peso+caminho;
        }
        p=p->prox;
      }
      g->visitados[i]=1;
      cont++;
    }
  }
  for (int i = 0; i < g->nos; i++) {
    g->visitados[i] = 0;
  }
  return menor_dist;
}

void busca_profundidade(Grafo *g, char ini) {
  printf("%c\n", ini);
  g->visitados[ini % 65] = 1;
  No *vizinho = g->viz[ini % 65];
  while (vizinho != NULL) {
    while (g->visitados[vizinho->letra % 65] != 0) {
      vizinho = vizinho->prox;
      if (vizinho == NULL) {
        return;
      }
    }
    busca_profundidade(g, vizinho->letra);
  }
  for (int i = 0; i < g->nos; i++) {
    g->visitados[i] = 0;
  }
  return;
}
