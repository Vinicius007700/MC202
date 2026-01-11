#include "improbabilidade.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int c, a, peso_total = 0, melhor_improb;
    scanf("%d %d", &c, &a);

    circuito *todos_circuitos = cria_vetor_com_todos_circuitos(c, a, &peso_total);
    int * melhor_sequencia = encontra_melhor_permutacao(todos_circuitos, c, a, peso_total, &melhor_improb);

    print_resp(melhor_sequencia, melhor_improb, a);
    
    free(melhor_sequencia);
    libera_todos_circuitos(todos_circuitos, c);
    
    return 0;
}