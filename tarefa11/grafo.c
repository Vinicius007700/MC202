#include <stdlib.h>
#include "piscapisca.h"


p_grafo criar_grafo(int n)
{
    int i, j;
    p_grafo g = malloc(sizeof(struct grafo));
    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
    {
        g->adj[i] = malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->adj[i][j] = 0;

    return g;
}

void insere_conexao(p_grafo grafo, int conex_1, int conex_2, int s)
{
    grafo->adj[conex_1][conex_2] = 1;
    grafo->adj[conex_2][conex_1] = 1;
}
int *inicializa_ciclos(p_grafo g)
{
    int *ciclo = calloc(g->n, sizeof(int));
    return ciclo;
}
// Função que retorna o pai de um determinado vértice, ou seja, retorna um
// vértice anterior ao vértice atual no caminho
int encontrar_pai(p_grafo g, int v, int *visitado)
{
    for (int w = 0; w < g->n; w++)
    {
        if (g->adj[v][w] && visitado[w] == 1)
        {
            return w;
        }
    }
    return -1; // se não encontrar um pai
}

// Função que retorna o estado da led pai
enum estado estado_pai(no_chaves original, int num)
{
    if (original->num == num)
        return original->estado;
    else if (num > original->num)
        return estado_pai(original->dir, num);
    return (estado_pai(original->esq, num));
}
// Função que utilizando filas, percorre o grafo por largura e apaga as LEDs
// que estão apagadas
void operacoes_para_apagar_led(p_grafo g, int s, int *dist_minima, distancia_pontos distancia_pontos)
{
    int *visitado = (int *)calloc(g->n, sizeof(int)); 
    p_fila f = criar_fila();                         
    enfileira(f, s);                                  
    visitado[s] = 1;                                 

    while (!fila_vazia(f))
    {
        int v = desenfileira(f);
        if (dist_minima[v] != -1)
        { 
            if (v != s)
            {                                           
                int pai = encontrar_pai(g, v, visitado); 

                // Verifica o estado do pai, pois se o pai 
                // da led está apagado ou queimado, a led está apagada
                if (pai != -1 && estado_pai(distancia_pontos[dist_minima[v]].chave, v) == acesa &&
                    (estado_pai(distancia_pontos[dist_minima[pai]].chave, pai) == queimada ||
                     estado_pai(distancia_pontos[dist_minima[pai]].chave, pai) == apagada))
                {
                    troca_para_led_apagada(distancia_pontos[dist_minima[v]].chave, v);
                }
            }
        }

        for (int w = 0; w < g->n; w++)
        {
            if (g->adj[v][w] && !visitado[w])
            {                    
                visitado[w] = 1; 
                enfileira(f, w);
            }
        }
    }

    free(visitado);   
    destruir_fila(f); 
}