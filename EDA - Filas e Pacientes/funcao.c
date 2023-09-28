#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ficha *cria_ficha(char *faixa, int num) {
  Ficha *ficha = (Ficha *)malloc(sizeof(Ficha));
  if (ficha == NULL) {
    fprintf(stderr, "Erro ao alocar memoria\n");
    exit(90);
  }
  return ficha;
}
Ficha *fila_atendimento(Ficha *lst, char *faixa, int num) {
  Ficha *nova = cria_ficha(faixa, num);
  strcpy(nova->cor, faixa);
  nova->chegada = num;
  if (lst == NULL) {
    lst = nova;
    lst->prox = NULL;
    return lst;
  } else {
    Ficha *ant = NULL;
    Ficha *p = lst;
    if (strcmp(faixa, "vermelho") == 0) {
      while (p != NULL && num > p->chegada) {
        if (strcmp(p->cor, "amarelo") == 0 || strcmp(p->cor, "verde") == 0) {
          if (!ant) {
            nova->prox = p;
            lst = nova;
          } else {
            ant->prox = nova;
            nova->prox = p;
          }
          return lst;
        }
        ant = p;
        p = p->prox;
      }
      if (!ant) {
        nova->prox = p;
        lst = nova;
      } else {
        ant->prox = nova;
        nova->prox = p;
      }
      return lst;
    } else if (strcmp(faixa, "amarelo") == 0) {
      while (strcmp(p->cor, "vermelho") == 0) {
        if (p->prox == NULL) {
          nova->prox = p->prox;
          p->prox = nova;
          return lst;
        }
        ant = p;
        p = p->prox;
      }
      while (p != NULL && num > p->chegada) {
        if (strcmp(p->cor, "verde") == 0) {
          if (!ant) {
            nova->prox = p;
            lst = nova;
          } else {
            ant->prox = nova;
            nova->prox = p;
          }
          return lst;
        }
        ant = p;
        p = p->prox;
      }
      if (!ant) {
        nova->prox = p;
        lst = nova;
      } else {
        ant->prox = nova;
        nova->prox = p;
      }
      return lst;
    } else if (strcmp(faixa, "verde") == 0) {
      while (p != NULL && (strcmp(p->cor, "vermelho") == 0 ||
                           strcmp(p->cor, "amarelo") == 0)) {
        if (p->prox == NULL) {
          nova->prox = p->prox;
          p->prox = nova;
          return lst;
        }
        ant = p;
        p = p->prox;
      }
      while (p != NULL && num > p->chegada) {
        ant = p;
        p = p->prox;
      }
      if (!ant) {
        nova->prox = lst;
        lst = nova;
      } else {
        ant->prox = nova;
        nova->prox = p;
      }
      return lst;
    } else {
      free(nova);
      fprintf(stderr, "Informacao Desconhecida\n");
      exit(100);
    }
  }
}

void exibe_atendimento(Ficha *lst) {
  Ficha *p = lst;
  int vermelho = 0;
  int amarelo = 0;
  int verde = 0;
  printf("Lista de Pacientes:\n");

  while (p) {
    if (strcmp(p->cor, "vermelho") == 0) {
      vermelho++;
    } else if (strcmp(p->cor, "amarelo") == 0) {
      amarelo++;
    } else if (strcmp(p->cor, "verde") == 0) {
      verde++;
    }
    printf("Paciente: %d\nEstado de leito: %s", p->chegada, p->cor);
    puts("\n\n");
    p = p->prox;
  }
  printf("Filas por Prioridade:\n");
  printf("Vermelha: %d\nAmarelo: %d\nVerde: %d", vermelho, amarelo, verde);
  puts("\n\n");

  return;
}
Ficha *paciente_atendido(Ficha *lst, int num) {
  Ficha *ant = NULL;
  Ficha *p = lst;
  while (p) {
    if (p->chegada == num) {
      if (!ant) {
        lst = p->prox;
      } else {
        ant->prox = p->prox;
      }
      free(p);
      exibe_atendimento(lst);
      return lst;
    }
    ant = p;
    p = p->prox;
  }
  fprintf(stderr, "Paciente Inexistente\n");
  exit(200);
}

void limpa_atendimento(Ficha *lst) {
  Ficha *p = lst;
  Ficha *seguinte;
  while (p) {
    seguinte = p->prox;
    free(p);
    p = seguinte;
  }
  return;
}