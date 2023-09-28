#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE *arq;
  char frase[4524];
  int *v = malloc(TAM * sizeof(int));
  for (int i = 0; i < TAM; i++) {
    v[i] = 0;
  }
  arq = fopen("texto.txt", "r");
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    exit(-9);
  }
  while (fgets(frase, sizeof(frase), arq) != NULL) {
    printf("%s\n\n", frase);
  }

  for (int i = 0; i < strlen(frase); i++) {
    int indice = frase[i];
    printf("Indice:%4d Letra:%c Freq:%d\n", indice, indice, v[indice] + 1);
    v[indice]++;
  }

  printf("\nMontando a Lista Encadeada\n");
  Lista *lista_cod = (Lista *)malloc(sizeof(Lista));
  if (lista_cod == NULL) {
    printf("Erro ao alocar o espaco.\n");
    exit(-10);
  }
  monta_lista(v, lista_cod);

  fclose(arq);

  printf("\nResultado:\n\n");
  No *p = lista_cod->inicio;
  while (p) {
    printf("%d,%c\n", p->freq, p->caracter);
    p = p->prox;
  }
  monta_arvore(lista_cod);
  printf("\nArvore Binária Construida\n");
  exibe_preordem(lista_cod->inicio);

  int h = altura_arv(lista_cod->inicio);

  char **dicionario = (char **)malloc(sizeof(char *) * TAM);
  if (dicionario == NULL) {
    printf("Erro ao alocar o espaco.\n");
    exit(-10);
  }
  for (int i = 0; i < TAM; i++) {
    dicionario[i] = (char *)calloc(h + 1, sizeof(char));
    if (dicionario[i] == NULL) {
      printf("Erro ao alocar o espaco.\n");
      exit(-10);
    }
  }
  char codigo[h];
  printf("\nDicionário\n");

  monta_dicionario(dicionario, lista_cod->inicio, codigo, 0);

  printf("\nResultado Codificado:\n");

  arq = fopen("codigo.bin", "wb");

  char *codificado = codifica(dicionario, frase, arq);
  printf("\n%s\n", codificado);

  fclose(arq);
  arq = fopen("codigo.bin", "rb");

  char *descodificado = decode(arq, lista_cod->inicio);

  printf("\nResultado Descodificado:\n");
  printf("\n%s\n\n", descodificado);

  FILE *arq2;
  int tam1, tam2;
  arq2 = fopen("texto.txt", "r");
  fseek(arq, 0, SEEK_END);
  fseek(arq2, 0, SEEK_END);
  tam1 = ftell(arq);
  tam2 = ftell(arq2);

  printf("Tamanho do arquivo texto: %ld bytes\nTamanho do arquivo binário: %ld "
         "bytes\n",
         tam1, tam2);

  fclose(arq);
  return 0;
}
