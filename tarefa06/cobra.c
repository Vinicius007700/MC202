#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobra.h"
typedef struct matriz *posicoes;
typedef struct cobra *cobra;
typedef struct cabeca *cabeca;

cobra inicializar_corpo_cobra(int linha, int coluna)
{
    cobra elemento = malloc(sizeof(struct cobra));
    if (elemento == NULL)
    {
        perror("falha ao alocar memória para corpo da cobra");
        exit(EXIT_FAILURE);
    }
    elemento->prox = NULL;
    elemento->ant = NULL;
    elemento->linha = linha;
    elemento->coluna = coluna;
    return elemento;
}

// função que adiciona a cabeça, quando a cobrinha é inicializada
cabeca inicializar_cabeca(cobra cobra)
{
    cabeca cabeca = malloc(sizeof(struct cabeca));
    if (cabeca == NULL)
    {
        perror("Falha ao alocar memória para a cabeça da cobra");
        exit(EXIT_FAILURE);
    }
    cabeca->inicio = cobra;
    cabeca->rabo = cobra;
    cabeca->len_cobra = 1;
    return cabeca;
}
// cria o campo de jogo que será armazenado em uma matriz, adicionando a posição da cabeça inicial
char **criar_matriz(int linha_incial_cobra, int col_inicial_cobra, int num_linhas, int num_colunas)
{
    char **matriz = malloc(num_linhas * sizeof(char *));
    if (matriz == NULL)
    {
        perror("Erro ao alocar memória para matriz");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_linhas; i++)
    {
        matriz[i] = malloc(num_colunas * sizeof(char));
        if (matriz[i] == NULL)
        {
            perror("Erro ao alocar memória para as colunas da matriz");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < num_colunas; j++)
        {
            matriz[i][j] = '_';
        }
    }

    matriz[linha_incial_cobra][col_inicial_cobra] = '#';
    return matriz;
}
// função que atualiza a posição da cabeça e de todas as partes da cobrinha, começando pelo rabo e indo para cabeça,
// de trás para cima
cabeca movimentacao_cabeca(cabeca original, int nova_linha, int nova_coluna)
{
    cobra atual = original->rabo;
    while (atual->ant != NULL)
    { // o atual recebe o valor de linha e coluna de seu anterior.
        atual->linha = atual->ant->linha;
        atual->coluna = atual->ant->coluna;
        atual = atual->ant;
    }
    // o primeiro elemento que é a nova cabeça recebe o valor da nova linha e nova coluna
    original->inicio->linha = nova_linha;
    original->inicio->coluna = nova_coluna;

    return original;
}
// função que adiciona uma cabeça, quando a cobrinha come uma fruta.
cabeca adicionar_cabeca(cabeca original, int linha, int coluna)
{
    cobra novo = malloc(sizeof(struct cobra));
    if (novo == NULL)
    {
        perror("Falta alocar memória para novo");
        exit(EXIT_FAILURE);
    }
    novo->linha = linha;
    novo->coluna = coluna;
    novo->prox = original->inicio;
    original->inicio->ant = novo;
    novo->ant = NULL;
    original->inicio = novo;
    original->len_cobra++;
    return original;
}
//função que altera os ponteiros de nova_coluna e nova_linha
void determinar_nova_pos(char comando, cabeca cabeca, cobra corpo_cobra, int num_linhas, int num_colunas, int * nova_linha, int * nova_coluna)
{
    int cont;
    if (comando == 'w' || comando == 's'){ // se a cobra vai para cima ou para baixo a nova_coluna permanece a mesma
        * nova_coluna = cabeca->inicio->coluna;
        cont = (comando == 'w') ? -1 : 1;
        * nova_linha = (cabeca->inicio->linha + num_linhas + cont) % num_linhas;
    }

    else{ // se a cobra vai para esquerda ou para direita a nova_linha permanece a mesma
        * nova_linha = cabeca->inicio->linha;
        cont = (comando == 'd') ? 1 : -1;
        * nova_coluna = (cabeca->inicio->coluna + num_colunas + cont) % num_colunas;
    }


}
// função que atualiza o campo da cobrinha e retoma falso se o usuário
// perdeu o jogo e verdadeiro se ganhou
int movimentacao_tabuleiro(char comando, char **matriz, cobra corpo_cobra, cabeca cabeca,
                           int num_linhas, int num_colunas)
{
    int nova_linha, nova_coluna;
    determinar_nova_pos(comando, cabeca, corpo_cobra, num_linhas, num_colunas, &nova_linha, &nova_coluna);
    if (matriz[nova_linha][nova_coluna] == '#')
    {

        return 0;
    }
    else if (matriz[nova_linha][nova_coluna] == '_')
    {
        matriz[nova_linha][nova_coluna] = '#';
        matriz[cabeca->rabo->linha][cabeca->rabo->coluna] = '_';
        cabeca = movimentacao_cabeca(cabeca, nova_linha, nova_coluna);
    }
    else
    {
        matriz[nova_linha][nova_coluna] = '#';
        cabeca = adicionar_cabeca(cabeca, nova_linha, nova_coluna);
    }

    return 1;
}
// função que printa o tabuleiro
void print_tabuleiro(char **matriz, int num_linhas, int num_colunas)
{
    for (int i = 0; i < num_linhas; i++)
    {
        for (int j = 0; j < num_colunas; j++)
            printf("%c ", matriz[i][j]);
        printf("\n");
    }
    printf("\n");
}
// função que libera o corpo da cobra e a sua cabeça
void free_corpo_cobra(cabeca cabeca)
{
    cobra corpo = cabeca->inicio;
    cobra temp;
    while (corpo != NULL)
    {
        temp = corpo->prox;
        free(corpo);
        corpo = temp;
    }
    free(cabeca);
}
// função que libera a matriz
void free_matriz(char **matriz, int num_linhas)
{
    for (int i = 0; i < num_linhas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}
