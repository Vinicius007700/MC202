#include "centros.h"
// Funções de fila de prioridades


//Funções de grafos
p_grafo inicializa_grafo(p_hash t)
{
    int i;
    p_grafo g = malloc(sizeof(struct grafo));
    g->n = MAX_HASH;
    g->adj = malloc(MAX_HASH * sizeof(p_no));
    for (i = 0; i < MAX_HASH; i++)
        g->adj[i] = NULL;
    return g;
}
grafo_no insere_na_lista(grafo_no lista, int chave, int peso)
{
    grafo_no novo = malloc(sizeof(struct g_no));
    novo->chave = chave;
    novo->prox = lista;
    novo->peso = peso;
    return novo;
}
void libera_grafo(p_grafo g)
{
    for (int i = 0; i < MAX_HASH; i++)
    {
        grafo_no atual = g->adj[i];
        while (atual != NULL)
        {
            grafo_no temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}
void insere_aresta(p_grafo g, int u, int v, int peso)
{
    g->adj[v] = insere_na_lista(g->adj[v], u, peso);
    g->adj[u] = insere_na_lista(g->adj[u], v, peso);
}
// Função que utiliza o algoritmo de dijkstra para retornar um vetor de distâncias de um determinada determinada cidade a todos as outras.
int *dijkstra(p_grafo g, int s)
{
    int *pai = malloc(MAX_HASH * sizeof(int));
    int *dist = malloc(MAX_HASH * sizeof(int));
    for (int i = 0; i < MAX_HASH; i++)
    {
        dist[i] = -1;
    }
    p_fp h = criar_fprio(g->n);

    for (int v = 0; v < g->n; v++)
    {
        if (g->adj[v] != NULL)
        {
            pai[v] = -1;
            dist[v] = INFINITO;
            item item = {v, INFINITO};
            insere(h, item);
        }
    }
    dist[s] = 0;
    pai[s] = s;
    diminui_prioridade(h, s, 0);

    while (!vazia(h))
    {
        int v = extrai_minimo(h);
        for (grafo_no t = g->adj[v]; t != NULL; t = t->prox)

            if (dist[v] + t->peso < dist[t->chave]) 
            {
                dist[t->chave] = dist[v] + t->peso;             
                pai[t->chave] = v;                               
                diminui_prioridade(h, t->chave, dist[t->chave]); 
            }
    }
    free(h->v);
    free(h);
    free(pai);

    return dist;
}





