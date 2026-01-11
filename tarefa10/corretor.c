#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corretor.h"
#define MAX 193 // um número primo distante de duas bases de dois
#define MAX_STRING 25
/*string que será a responsável por realizar as trocas de caracteres.
 O  @ simboliza uma palavra que foi inserida a mais*/
char *trocas = "abcdefghijklmnopqrstuvwxyz@";
// Função que determina a chave do hash
int hash(char *chave)
{
    int i = 0, n = 0;
    for (i = 0; i < strlen(chave); i++)
    {
        if (chave[i] != '@') // Se não for @, pois @ é considerado um caractere inválido
            n = (256 * n + chave[i]) % MAX;
    }
    return n;
}

// Função para criar o hash inicialmente, sem nenhuma informação. Apenas para alocar memória
p_hash criar_hash()
{
    p_hash t = malloc(sizeof(struct hash));
    for (int i = 0; i < MAX; i++)
    {
        t->vetor[i] = NULL;
    }
    return t;
}
// Função para inserir os elementos no dicionário
p_no inserir_dic(p_no original, char *chave)
{

    p_no novo = malloc(sizeof(struct no));
    strncpy(novo->chave, chave, MAX_STRING);
    novo->prox = NULL;
    if (original == NULL)
    {
        original = novo;
    }
    else
    { // Se já há outro elemento nesta mesma chave, nós temos que colocar no prox
        p_no atual = original;
        while (atual != NULL && atual->prox != NULL)
            atual = atual->prox;
        atual->prox = novo;
    }
    return original;
}
// Função que insere no dicionário, mas esta é a mais geral.
void inserir(p_hash t, char *chave)
{
    int n = hash(chave);
    t->vetor[n] = inserir_dic(t->vetor[n], chave);
}

// Função que compara duas strings, desconsiderando o @ caso ele apareça, retornando 0 para iguais e 1 para diferentes.
int comparar_strings_alteradas(char *alterada, char *original)
{
    for (int i = 0, cont_alterada = 0; i < strlen(original); i++, cont_alterada++)
    {
        if (alterada[cont_alterada] == '@')
            cont_alterada++; // Temos que descosiderar o @ na contagem
        if (alterada[cont_alterada] != original[i])
            return 1;
    }
    return 0;
}
// Função para verificar se uma determinada chave não há alterações
enum cores sem_alteracoes(p_hash dic, char *palavra)
{
    int n = hash(palavra);
    p_no atual = dic->vetor[n];
    while (atual != NULL)
    {
        if (comparar_strings_alteradas(palavra, atual->chave) == 0)
            return verde;
        atual = atual->prox;
    }
    return indeterminado;
}
// Função responsávvel por verificar se há algum elemento trocado ou algum elemento em excesso.
enum cores trocado_ou_1_excesso(p_hash dic, char *palavra)
{
    char palavra_alterada[MAX_STRING];
    for (int i = 0; i < strlen(palavra); i++)
    {
        strcpy(palavra_alterada, palavra);
        for (int j = 0; j < strlen(trocas); j++)
        {
            palavra_alterada[i] = trocas[j];
            if (sem_alteracoes(dic, palavra_alterada) == verde) // Se a nossa nova palavra com uma alteração for verde
                return amarelo;                                 // então, houve apenas uma mudança
        }
    }
    return indeterminado;
}
// Função que adiciona na string um caractere por meio de concatenação
void adicionar_na_string_caractere(char *palavra, char caractere, char *palavra_alterada, int posicao_adicionar)
{
    char comeco_string[MAX_STRING], final_string[MAX_STRING];
    comeco_string[0] = '\0'; // vamos inicializar as strings
    final_string[0] = '\0';
    for (int i = 0; i < posicao_adicionar; i++)
        comeco_string[i] = palavra[i];            // Adicionando os caracteres que estarão antes do novo caractere
    comeco_string[posicao_adicionar] = caractere; // Adicionado o novo caractere em sua posição
    comeco_string[posicao_adicionar + 1] = '\0';  // Marcando o fim da string inicial
    for (int i = 0; i < strlen(palavra) - posicao_adicionar; i++)
    {
        final_string[i] = palavra[i + posicao_adicionar]; // Adicionando os caracteres que estarão depois do novo caractere
    }
    final_string[strlen(palavra) - posicao_adicionar] = '\0'; // Marcando o fim da string final
    strcat(comeco_string, final_string);                      // Concatenando as duas strings
    strcpy(palavra_alterada, comeco_string);
}
// Função que organiza quais caracteres terão que serem adicionados
enum cores adicionar_faltando(p_hash dic, char *palavra)
{
    char palavra_alterada[MAX_STRING];
    for (int i = 0; i < strlen(palavra) + 1; i++)
    { // i representa a posição de adicionar o determinado caractere
        for (int j = 0; j < strlen(trocas); j++)
        {
            adicionar_na_string_caractere(palavra, trocas[j], palavra_alterada, i);
            if (sem_alteracoes(dic, palavra_alterada) == verde) // Se a nova palavra estiver no dicionário,
                return amarelo;                                 // então, concluimos que houve 1 alteração
        }
    }
    return vermelho; // Se nós não concluímos que é amarelo, podemos dizer que é vermelho
}
// Função que determina qual a cor será atribuída a palavra
enum cores determinar_nivel_correcao(p_hash dic, char *palavra)
{
    if (sem_alteracoes(dic, palavra) == verde)
        return verde;
    if (trocado_ou_1_excesso(dic, palavra) == amarelo)
        return amarelo;
    return (adicionar_faltando(dic, palavra));
}
// Função que printa as respostas, dizendo o nome da palavra e qual cor ela receberá.
void print_respostas(enum cores resposta, char *palavra)
{
    printf("%s:", palavra);
    if (resposta == verde)
        printf(" verde\n");
    else if (resposta == amarelo)
        printf(" amarelo\n");
    else
        printf(" vermelho\n");
}
// Função que libera o hash interativamente
void liberar_hash(p_hash dic)
{
    for (int i = 0; i < MAX; i++)
    {
        p_no liberado = dic->vetor[i];
        while (liberado != NULL)
        {
            p_no prox = liberado->prox;
            free(liberado);
            liberado = prox;
        }
    }
    free(dic);
}