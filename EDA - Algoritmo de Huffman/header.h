#include <stdio.h>
#define TAM 127
typedef struct no No;
typedef struct lista Lista;

// no encadeados
struct no {
  char caracter;
  int freq;
  No *esq;
  No *dir;
  No *prox;
};
// lista encadeada
struct lista {
  No *inicio;
  int tam;
};

// monta a fila encadeada
void insere_cresc(Lista *lst, No *chave);
void monta_lista(int *v, Lista *lst);
No *cria_no(No *folha, int chave, int freq, No *esq, No *dir);
// monta a arvore binaria
No *remove_no(Lista *inicio);
void *monta_arvore(Lista *inicio);
void exibe_preordem(No *inicio);
// monta o dicionário
int altura_arv(No *inicio);
void monta_dicionario(char **dicionario, No *inicio, char *caminho, int nivel);
// cria código
int tam_cod(char **dicionario, char *texto);
char *codifica(char **dicionario, char *texto, FILE *arq);
// decodifica
char *decode(FILE *arq, No *inicio);