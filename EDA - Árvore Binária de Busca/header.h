typedef struct arvore Arvore;

int max(int a,int b);
int mesmo_n(int n, int* list);
void exibe_pre(Arvore* p);
Arvore* cria_arv(int x, Arvore* esq, Arvore* dir);
Arvore* insere_bb(Arvore* p, int x);
int checa_abb(Arvore* p);
int altura_a(Arvore* p);

struct arvore {
    int info;
    Arvore* esq;
    Arvore* dir;
};
