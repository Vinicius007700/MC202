#include <stdio.h>
#include <stdlib.h>
#include "piscapisca.h"

p_fila criar_fila()
{
    p_fila f;
    f = malloc(sizeof(struct fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}
void destruir_lista(p_no inicio)
{
    p_no temp;
    while (inicio != NULL)
    {
        temp = inicio;
        inicio = inicio->prox;  
        free(temp);           
    }
}
void destruir_fila(p_fila f)
{
    destruir_lista(f->ini);
    free(f);
}
int fila_vazia(p_fila f)
{
    return f->ini == NULL; 
}

void enfileira(p_fila f, int x)
{
    p_no novo;
    novo = malloc(sizeof(struct p_no));
    novo->dado = x;
    novo->prox = NULL;
    if (f->ini == NULL)
        f->ini = novo;
    else
        f->fim->prox = novo;
    f->fim = novo;
}
int desenfileira(p_fila f)
{
    p_no primeiro = f->ini;
    int x = primeiro->dado;
    f->ini = f->ini->prox;
    if (f->ini == NULL)
        f->fim = NULL;
    free(primeiro);
    return x;
}


distancia_pontos inicializa_dist_pontos(int n)
{
    distancia_pontos dist_pontos = malloc(n * sizeof(struct distancia_pontos));
    if (!dist_pontos)
    {
        perror("Falha ao alocar memória para dist_pontos");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++)
    {
        dist_pontos[i].chave = NULL; 
    }
    return dist_pontos;
}

// função que insere um determinado número dentro de no_chaves(que todos os ele-
// mentos já estão na mesma distância), em uma árvore binária
no_chaves inserir_chaves(no_chaves original, int atual)
{
    if (original == NULL)
    {
        no_chaves novo = malloc(sizeof(struct no_chaves));
        novo->dir = novo->esq = NULL;
        novo->estado = acesa;
        novo->num = atual;
        return novo;
    }
    if (atual < original->num)
        original->esq = inserir_chaves(original->esq, atual);
    else
        original->dir = inserir_chaves(original->dir, atual);
    return original;
}
// Função que determina a distância de um ponto ao elemento inicial do circuito
void determinar_distancias_da_raiz(p_grafo g, int s, int *dist_minima)
{
    int *visitado = (int *)calloc(g->n, sizeof(int));
    p_fila f = criar_fila();
    enfileira(f, s);
    visitado[s] = 1;
    dist_minima[s] = 0;
    while (!fila_vazia(f))
    {
        int v = desenfileira(f);
        for (int w = 0; w < g->n; w++)
        {
            if (g->adj[v][w] && !visitado[w])
            {
                visitado[w] = 1;
                enfileira(f, w);
                dist_minima[w] = dist_minima[v] + 1; // o filho (W) terá a distância aumentada
                                                    // em 1 em relação ao pai
            }
        }
    }

    free(visitado);   
    destruir_fila(f); 
}


int detectar_ciclo(p_grafo g, int i, int *visitado, int *caminho, int ant, int *atual, int *ciclos)
{

    visitado[i] = indeterminado; // não sabemos o que o estado da LED
    caminho[(*atual)++] = i; 

    for (int j = 0; j < g->n; j++)
    {
        if (g->adj[i][j])
        { 
            if (visitado[j] == fora_ciclo)
            {                                                              // Visite o próximo nó não explorado
                detectar_ciclo(g, j, visitado, caminho, i, atual, ciclos); // Continua a busca
            }
            else if (j != ant && visitado[j] == indeterminado)
            {
                // Encontramos o ciclo, registra todos os nós do ciclo
                for (int k = *atual - 1; k >= 0 && caminho[k] != j; k--)
                {
                    ciclos[caminho[k]] = 1; 
                }
                ciclos[j] = 1; // Marca o primeiro elemento do ciclo
            }
        }
    }

    visitado[i] = percorrido; //para marcar que já percorremos determinado elemento
    (*atual)--; 
    return 0;   
}
// Definimos determinada LED para queimada
void troca_arvore_binaria_para_led_queimada(no_chaves original, int num)
{
    if (original->num == num)
    {
        original->estado = queimada;
    }
    else if (num > original->num)
        troca_arvore_binaria_para_led_queimada(original->dir, num);
    else if (num < original->num)
        troca_arvore_binaria_para_led_queimada(original->esq, num);
}


distancia_pontos atualiza_led_queimadas(distancia_pontos original, int *ciclo, int n, int *dist_minima)
{
    for (int i = 0; i < n; i++)
    {
        if (ciclo[i] == 1 && dist_minima[i] != -1)
            troca_arvore_binaria_para_led_queimada(original[dist_minima[i]].chave, i);
    }
    return original;
}
distancia_pontos identifica_ciclos(p_grafo g, distancia_pontos original, int *dist_minima, int s, int *ciclo)
{
    int *visitado = malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++)
    {
        visitado[i] = fora_ciclo;
    }
    int *caminho = malloc(g->n * sizeof(int));
    int atual = 0;
    for (int i = 0; i < g->n; i++)
        if (visitado[i] == fora_ciclo)
            detectar_ciclo(g, s, visitado, caminho, -1, &atual, ciclo);
    original = atualiza_led_queimadas(original, ciclo, g->n, dist_minima);
    free(visitado);
    free(caminho);
    return original;
}
// Função que insere a distância de um determinado ponto em relação a raiz
no_chaves inserir_dist_pontos(no_chaves original, int num)
{
    if (original == NULL)
    {
        no_chaves novo = malloc(sizeof(struct no_chaves));
        if (novo == NULL)
        {
            perror("Falha ao alocar memoria");
            exit(EXIT_FAILURE);
        }
        novo->dir = novo->esq = NULL;
        novo->estado = acesa;
        novo->num = num;
        return novo;
    }
    if (num < original->num)
        original->esq = inserir_dist_pontos(original->esq, num);
    else
        original->dir = inserir_dist_pontos(original->dir, num);
    return original;
}
// Função que troca o estado de uma LED para apagada
void troca_para_led_apagada(no_chaves original, int num)
{
    if (original->num == num)
        original->estado = apagada;
    else if (num > original->num)
        troca_para_led_apagada(original->dir, num);
    else if (num < original->num)
        troca_para_led_apagada(original->esq, num);
}
// função que printa os elementos em ordem
void printar_leds_por_num(no_chaves chaves, int dist)
{
    if (chaves == NULL)
        return;

    printar_leds_por_num(chaves->esq, dist);
    printf("%d a distancia %d: %s\n", chaves->num, dist,
           chaves->estado == acesa ? "acesa" : chaves->estado == queimada ? "queimada"
                                                                          : "apagada");

    printar_leds_por_num(chaves->dir, dist);
}

void printar_leds_ordenadas_distancia_pontos(distancia_pontos dist_pontos, int n)
{
    for (int dist = 0; dist < n; dist++)
    {
        if (dist_pontos[dist].chave != NULL)
        {
            printar_leds_por_num(dist_pontos[dist].chave, dist);
        }
    }
}
void liberar_dist_pontos(no_chaves original)
{
    if (original == NULL)
        return;
    liberar_dist_pontos(original->dir);
    liberar_dist_pontos(original->esq);
    free(original);
}

void liberar_tudo(p_grafo g, int * ciclo, int * dist_minima, distancia_pontos dist_pontos){
    free(dist_minima);
    free(ciclo);
    for (int i = 0; i < g->n; i++)
    {
        liberar_dist_pontos(dist_pontos[i].chave);
    }
    free(dist_pontos);
    for (int i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);
}

