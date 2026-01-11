#include "piscapisca.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, s, conex_1, conex_2;
    p_grafo grafo;
    int *ciclo;
    scanf("%d %d %d", &n, &m, &s);
    grafo = criar_grafo(n);
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &conex_1, &conex_2);
        insere_conexao(grafo, conex_1, conex_2, s);
    }
    int *dist_minima = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        dist_minima[i] = -1;
    }
    determinar_distancias_da_raiz(grafo, s, dist_minima);
    distancia_pontos distancia_pontos = inicializa_dist_pontos(n);
    for (int i = 0; i < grafo->n; i++)
    {
        if (dist_minima[i] != -1) // o i é o número
            distancia_pontos[dist_minima[i]].chave = inserir_dist_pontos(distancia_pontos[dist_minima[i]].chave, i);
    }
    ciclo = inicializa_ciclos(grafo);
    distancia_pontos = identifica_ciclos(grafo, distancia_pontos, dist_minima, s, ciclo);
    operacoes_para_apagar_led(grafo, s, dist_minima, distancia_pontos);
    printar_leds_ordenadas_distancia_pontos(distancia_pontos, n);
    liberar_tudo(grafo, ciclo, dist_minima, distancia_pontos);
    return 0;
}