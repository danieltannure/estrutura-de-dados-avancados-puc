typedef struct ficha Ficha;

struct ficha {
  char cor[20];
  int chegada;
  Ficha *prox;
};

Ficha *fila_atendimento(Ficha *lst, char *faixa, int num);
Ficha *cria_ficha(char *faixa, int num);
Ficha *paciente_atendido(Ficha *lst, int num);
void limpa_atendimento(Ficha*lst);
void exibe_atendimento(Ficha *lst);