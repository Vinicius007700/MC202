#include "centros.h"
// Função de inicialização das distâncias
distancias inicializa_distancias(p_hash t)
{
    distancias dist = malloc(MAX_HASH * sizeof(struct distancias));
    for (int i = 0; i < MAX_HASH; i++)
    {
        dist[i].vetor = malloc(MAX_HASH * sizeof(int));
        dist[i].populacao = 0;
        for (int j = 0; j < MAX_HASH; j++)
        {
            if (i != j)
                dist[i].vetor[j] = INFINITO;
            else
                dist[i].vetor[j] = 0; // A distância de uma cidade para ela mesma é 0
        }
    }
    return dist;
}

/* Função que retorna a distância máxima de uma cidade até as outras*/
int determina_dist_maxima(int *centro_distribuicao, p_hash t)
{
    int max = -1;
    for (int i = 0; i < MAX_HASH; i++)
    {
        if (t->vetor[i] != NULL && max < centro_distribuicao[i])
        {
            max = centro_distribuicao[i];
        }
    }
    return max;
}
/*Função que insere as distâncias de um vetor dist que será obtido na função de dijkstra, para que nós possamos armazenar
esse vetor em outra estrutura que aproveita o hash dessea cidade*/
void inserir_distancias(distancias distancias, int *dist, p_hash t, int hash)
{
    for (int i = 0; i < MAX_HASH; i++)
    {
        if (t->vetor[i] != NULL && i != hash)
            distancias[hash].vetor[i] = dist[i];
    }
    distancias[hash].populacao = t->vetor[hash]->populacao;
}

cidade_escolhida *inicializa_cidade_escolhida(p_hash t)
{
    cidade_escolhida *cidade_escolhida = malloc(MAX_HASH * sizeof(struct cidade_escolhida));
    for (int i = 0; i < MAX_HASH; i++)
    {
        if (t->vetor[i] != NULL)
        {
            cidade_escolhida[i] = malloc(sizeof(struct cidade_escolhida));
            cidade_escolhida[i]->dist_min = INFINITO;
            cidade_escolhida[i]->hash_cidade = MAX_HASH + 1;
        }
    }
    return cidade_escolhida;
}
/* Função que faz a intercessão das distâncias entre duas cidades, sempre armazenando a menor distância*/
int *operacao_juntar_duas_cidades(int hash1, int hash2, distancias distancias, p_grafo g, p_hash t)
{
    int *juncao = malloc(MAX_HASH * sizeof(int));
    for (int i = 0; i < MAX_HASH; i++)
    {
        if (t->vetor[i] != NULL) // Se não há nenhuma cidade, vá para a próxima
        {
            if (g->adj[i] == NULL && t->vetor[i] != NULL && i != hash1 && i != hash2) // Se não há conexão entre as cidades, a distância é infinita
            {
                juncao[i] = INFINITO;
            }
            else if (distancias[hash1].vetor[i] > distancias[hash2].vetor[i])
                juncao[i] = distancias[hash2].vetor[i];
            else
                juncao[i] = distancias[hash1].vetor[i];
        }
    }
    return juncao;
}
/* Função que troca duas strings*/
void troca_string(char *str1, char *str2)
{
    char temp[MAX_STRING];
    strncpy(temp, str1, MAX_STRING);
    strncpy(str1, str2, MAX_STRING);
    strncpy(str2, temp, MAX_STRING);
}
/*Função que printa as respostas, sempre printando as cidades escolhidas em ordem alfabética*/
void printar_resposta(p_hash t, int hash1, int hash2, int maior_dist)
{
    char str1[MAX_STRING], str2[MAX_STRING];
    strncpy(str1, t->vetor[hash1]->chave, MAX_STRING);
    strncpy(str2, t->vetor[hash2]->chave, MAX_STRING);
    if (strcmp(str1, str2) > 0) // Se as strings não estão em ordem alfábetica, faça a troca
        troca_string(str1, str2);
    printf("Centros de distribuicao: %s e %s\n", str1, str2);
    printf("Distancia de atendimento: %d\n", maior_dist);
}



void libera_distancias(distancias d)
{
    for (int i = 0; i < MAX_HASH; i++)
    {
        free(d[i].vetor);
    }
    free(d);
}
//Função responsável por chamar as outras funções responsáveis por liberar as estruturas de dados
void libera_tudo(p_grafo g, p_hash t, distancias d)
{
    libera_grafo(g);
    libera_distancias(d);
    libera_hash(t);
}
/* Função que passa por referência três valores: maior_dist, hash da cidade 1 e hash da cidade 2, sendo valores que serão utilizados, para que nós
possamos determinar as três informações que serão necessárias para o print*/
void seleciona_cidades_centros_distribuicao(p_hash t, distancias distancias, p_grafo g, int *maior_dist, int *hash1, int *hash2)
{
    // Variável para entrar no if da linha 147, na primeira ocorrência.
    int verif = 1;
    for (int i = 0; i < MAX_HASH; i++)
    {
        if (t->vetor[i] != NULL)
            for (int j = 0; j < MAX_HASH; j++)
            {
                if (t->vetor[j] != NULL && i != j)
                {
                    int *juncao = operacao_juntar_duas_cidades(i, j, distancias, g, t);
                    int nova_maior_dist = determina_dist_maxima(juncao, t); // determina a maior distância do vetor de junção
                    free(juncao);
                    if (verif || nova_maior_dist < *maior_dist ||                                                          // verif explicado na linha de declaração de variável
                        (nova_maior_dist == *maior_dist && t->vetor[i]->populacao + t->vetor[j]->populacao >               // e a terceira condição é para caso as duas distâncias forem iguais
                                                               t->vetor[*hash1]->populacao + t->vetor[*hash2]->populacao)) // tenha o desempate pelo tamanho da população
                    {
                        *maior_dist = nova_maior_dist;
                        *hash1 = i;
                        *hash2 = j;
                        verif = 0;
                    }
                }
            }
    }
}
