#include "header.h"

int main(void) {
  No *vizA = montaNo('B', 5, montaNo('C', 4, montaNo('D', 2, NULL)));
  No *vizB = montaNo('A', 5, montaNo('C', 6, montaNo('E', 6, montaNo('H', 9, NULL))));
  No *vizC = montaNo('A', 4, montaNo('B', 6, montaNo('D', 3, montaNo('E', 4, NULL))));
  No *vizD = montaNo('A', 2, montaNo('C', 3, montaNo('E', 5, montaNo('F', 9, NULL))));
  No *vizE = montaNo('B', 6, montaNo('C', 4, montaNo('D', 5, montaNo('F', 2, montaNo('H', 6, NULL)))));
  No *vizF = montaNo('D', 9, montaNo('E', 2, montaNo('H', 3, NULL)));
  No *vizH = montaNo('B', 9, montaNo('E', 6, montaNo('F', 3, NULL)));
  
  No *viz[] = {vizA, vizB, vizC, vizD, vizE, vizF, NULL, vizH};
  
  Grafo *g = montaGrafo(N_NOS, viz);
  
  int *lista_dist_a = dist_curta(g, 'A');

  printf("Caminho mais curto para os vertices começando em: A\n\n");

  for (int i = 0; i < g->nos; i++) {
    printf("Dist %c: %d\n", i + 65, lista_dist_a[i]);
  }

  putchar('\n');
  printf("Busca em Profundidade começando em: A\n\n");
  
  busca_profundidade(g, 'A');
  return 0;
}

  
