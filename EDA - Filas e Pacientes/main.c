#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  Ficha *lst_atendimento = NULL;
  int caso=-1;
  int senha=1;
  char prioridade[20];
  do {
  printf("Digite:\n(1) Para inserir um paciente\n(2) Para atualizar o atendimento\n(3) Para verificar o estado da fila\n(0) Para fechar o sistema\n");
   scanf("%d",&caso);
    switch(caso){
      case 1:
      printf("Insira a prioridade do paciente ('vermelho','amarelo,'verde')\n");
      scanf(" %[^\n]", prioridade);
      printf("Inserindo paciente: %d na fila: %s\n",senha,prioridade);
      lst_atendimento=fila_atendimento(lst_atendimento,prioridade,senha);
      senha++;
      break;
      case 2:
      printf("Insira a senha do paciente atendido: \n");
      scanf("%d",&senha);
      lst_atendimento=paciente_atendido(lst_atendimento, senha);
      case 3:
      exibe_atendimento(lst_atendimento);
      break;
    }
  }
    while(caso!=0);
  limpa_atendimento(lst_atendimento);
  return 0;
}
