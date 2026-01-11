#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 15
#define MAX_HASH 107
#define INFINITO 100000
#define NUM_CENTRO_DISTRIBUICAO 2
#define PAI(i) ((i - 1) / 2)
#define F_ESQ(i) (2 * i + 1)
#define F_DIR(i) (2 * i + 2)
typedef struct grafo *p_grafo;
typedef struct g_no *grafo_no;
typedef struct no *p_no;
typedef struct hash *p_hash;
typedef struct FP *p_fp;
typedef struct item item;
typedef struct cidade_escolhida *cidade_escolhida;
typedef struct distancias *distancias;
struct distancias
{
    int *vetor, populacao;
};

struct cidade_escolhida
{
    int dist_min, hash_cidade, populacao_cidade;
};
struct item
{
    int v, dist;
};

struct FP
{
    item *v;
    int n, tamanho;
};

struct no
{
    char chave[MAX_STRING];
    int dist, populacao;
    p_no prox;
};
struct g_no
{
    int chave;
    int peso;
    grafo_no prox;
};
struct grafo
{
    grafo_no *adj;
    int n;
};

struct hash
{
    p_no vetor[MAX_HASH];
};
p_grafo inicializa_grafo(p_hash t);
p_hash criar_hash();

p_no inserir_lista(p_no original, char *chave, int populacao);
p_no inserir_lista(p_no original, char *chave, int populacao);

p_fp criar_fprio(int tam);

distancias inicializa_distancias(p_hash t);

void insere_aresta(p_grafo g, int u, int v, int peso);
void insere(p_fp fprio, item item);
void diminui_prioridade(p_fp fprio, int vertice, int nova_dist);
void inserir_distancias(distancias distancias, int *dist, p_hash t, int hash);
void seleciona_cidades_centros_distribuicao(p_hash t, distancias distancias, p_grafo g, int * maior_dist_original, int *hash1, int *hash2);
void printar_resposta(p_hash t, int hash1, int hash2, int maior_dist);
void libera_grafo(p_grafo g);
void libera_hash(p_hash t);
void libera_tudo(p_grafo g, p_hash t, distancias d);
void inserir_hash(p_hash t, char *chave, int populacao);

int hash(char *chave);
int *dijkstra(p_grafo g, int s);
int vazia(p_fp fprio);
int extrai_minimo(p_fp fprio);