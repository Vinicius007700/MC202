#include "centros.h"
p_hash criar_hash()
{
    p_hash t = malloc(sizeof(struct hash));
    for (int i = 0; i < MAX_HASH; i++)
    {
        t->vetor[i] = NULL;
    }
    return t;
}
int hash(char *chave)
{
    int n = 0;
    for (int i = 0; i < strlen(chave); i++)
    {
        n = (256 * n + chave[i]) % MAX_HASH;
    }
    return n;
}
p_no inserir_lista(p_no original, char *chave, int populacao)
{

    p_no novo = malloc(sizeof(struct no));
    strncpy(novo->chave, chave, MAX_STRING);
    novo->populacao = populacao;
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

void inserir_hash(p_hash t, char *chave, int populacao)
{
    int n = hash(chave);
    t->vetor[n] = inserir_lista(t->vetor[n], chave, populacao);
}

void libera_hash(p_hash t)
{
    for (int i = 0; i < MAX_HASH; i++)
    {
        p_no atual = t->vetor[i];
        while (atual != NULL)
        {
            p_no temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(t);
}