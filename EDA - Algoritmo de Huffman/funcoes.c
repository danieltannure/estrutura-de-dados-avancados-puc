#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

No *cria_no(No *folha, int chave, int freq, No *esq, No *dir) {
  folha = malloc(sizeof(No));
  if (folha == NULL) {
    printf("Erro ao alocar o espaco.\n");
    exit(-10);
  }
  folha->caracter = chave;
  folha->freq = freq;
  folha->esq = esq;
  folha->dir = dir;
  return folha;
}

void insere_cresc(Lista *lst, No *chave) {
  No *p;
  if (lst->inicio == NULL) {
    lst->inicio = chave;
    lst->tam++;
  } else if (lst->inicio->freq >= chave->freq) {
    chave->prox = lst->inicio;
    lst->inicio = chave;
    lst->tam++;
  } else {
    p = lst->inicio;
    while (p->prox && p->prox->freq <= chave->freq) {
      p = p->prox;
    }
    chave->prox = p->prox;
    p->prox = chave;
    lst->tam++;
  }

  return;
}

void monta_lista(int *v, Lista *lst) {
  No *letra = NULL;
  for (int i = 0; i < TAM; i++) {
    if (v[i] > 0) {

      letra = cria_no(letra, i, v[i], NULL, NULL);
      insere_cresc(lst, letra);
    }
  }
  return;
}

No *remove_no(Lista *lst) {
  No *aux;
  if (lst->inicio) {
    aux = lst->inicio;
    lst->inicio = aux->prox;
    aux->prox = NULL;
    lst->tam--;
  }
  return aux;
}

void *monta_arvore(Lista *inicio) {
  No *aux1, *aux2;
  No *soma = NULL;
  while (inicio->tam > 1) {
    aux1 = remove_no(inicio);
    aux2 = remove_no(inicio);

    soma = cria_no(soma, '+', aux1->freq + aux2->freq, aux1, aux2);
    insere_cresc(inicio, soma);
  }
}
void exibe_preordem(No *inicio) {
  if (!inicio) {
    return;
  }
  printf("chave: %c, freq:%d\n", inicio->caracter, inicio->freq);
  exibe_preordem(inicio->esq);
  exibe_preordem(inicio->dir);
}

int altura_arv(No *inicio) {
  int esq, dir;
  if (!inicio) {
    return -1;
  }
  esq = altura_arv(inicio->esq) + 1;
  dir = altura_arv(inicio->dir) + 1;
  if (esq > dir) {
    return esq;
  } else {
    return dir;
  }
}

void monta_dicionario(char **dicionario, No *inicio, char *codigo, int nivel) {
  if (inicio->esq == NULL && inicio->dir == NULL) {
    codigo[nivel] = '\0';
    printf("%c: %s(indice: %d)\n", inicio->caracter, codigo, inicio->caracter);
    strcpy(dicionario[inicio->caracter], codigo);
    return;
  }
  codigo[nivel] = '0';
  monta_dicionario(dicionario, inicio->esq, codigo, nivel + 1);
  codigo[nivel] = '1';
  monta_dicionario(dicionario, inicio->dir, codigo, nivel + 1);
}

int tam_cod(char **dicionario, char *texto) {
  int tam = 0;
  for (int i = 0; i < strlen(texto); i++) {
    tam += strlen(dicionario[texto[i]]);
  }
  return tam + 1;
}

char *codifica(char **dicionario, char *texto, FILE *arq) {
  int cont = 0;
  int tam = tam_cod(dicionario, texto);
  char *codigo = calloc(tam, sizeof(char));
  if (codigo == NULL) {
    printf("Erro ao alocar o espaco.\n");
    exit(-10);
  }
  while (cont < strlen(texto)) {
    char *num = dicionario[texto[cont]];
    strcat(codigo, num);
    cont++;
  }
  fwrite(codigo, sizeof(char), strlen(codigo), arq);
  return codigo;
}

char *decode(FILE *arq, No *inicio) {
  char texto[18410];
  fread(texto, sizeof(char), sizeof(texto), arq);
  int cont = 0;
  No *aux = inicio;
  No *p = inicio;
  char concatenado[2];
  char *resultado = calloc(strlen(texto), sizeof(char));
  if (resultado == NULL) {
    printf("Erro ao alocar o espaco.\n");
    exit(-10);
  }
  while (cont <= strlen(texto)) {
    if (p->esq == NULL && p->dir == NULL) {
      concatenado[0] = p->caracter;
      concatenado[1] = '\0';
      strcat(resultado, concatenado);
      p = aux;
    }
    if (texto[cont] == '0') {
      p = p->esq;
    } else if (texto[cont] == '1') {
      p = p->dir;
    }
    cont++;
  }

  return resultado;
}