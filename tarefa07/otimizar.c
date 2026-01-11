#include <stdio.h>
#include <stdlib.h>
typedef struct arvore *arvore;

struct arvore
{
    char info;
    arvore esq;
    arvore dir;
};
// função que dado um caractere, criar um no, com essa informação
arvore conectar_novo_no(char info)
{
    arvore novo = malloc(sizeof(struct arvore));
    if (novo == NULL)
    {
        perror("Falha ao alocar memória");
        exit(EXIT_FAILURE);
    }
    novo->info = info;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
// função que cria recursivamente a árvore pela primeira vez
arvore criar_galho()
{
    char caract;
    scanf(" %c", &caract);
    if (caract == '(')
    {
        arvore esq = criar_galho();
        scanf(" %c", &caract);
        arvore dir = criar_galho();
        getchar(); // para consumir o )
        arvore novo = conectar_novo_no(caract);
        novo->esq = esq;
        novo->dir = dir;
        return novo;
    }
    else if (caract == '!' || caract == '|' || caract == '&')
    {
        arvore esq = criar_galho();
        arvore novo = conectar_novo_no(caract);
        novo->esq = esq;
        return novo;
    }
    else
    {
        return conectar_novo_no(caract);
    }
}
// função que realiza as operações de Morgan, exceto a de dupla negação
arvore de_morgan(arvore original, int *cont)
{
    if (original == NULL)
    {
        return NULL;
    }
    if (original->info == '!')
    {
        if (original->esq != NULL)
        {
            if (original->esq->info == '|' || original->esq->info == '&')
            {
                arvore novo_esq = malloc(sizeof(struct arvore));
                arvore novo_dir = malloc(sizeof(struct arvore));
                if (novo_esq == NULL || novo_dir == NULL)
                {
                    perror("Falha ao alocar memória");
                    exit(EXIT_FAILURE);
                }
                novo_esq->dir = NULL;
                novo_dir->dir = NULL;
                novo_esq->info = '!';
                novo_dir->info = '!';
                original->info = (original->esq->info == '|') ? '&' : '|';
                novo_esq->esq = original->esq->esq; // as de linhas 78 e 79 são responsáveis por pular o original->esq, pois ele é o ! inicial
                novo_dir->esq = original->esq->dir;
                free(original->esq); // como o original->esq é o ! inicial, ele terá que ser removido, para não  haver erros de liberação de memória
                original->esq = novo_esq;
                original->dir = novo_dir;
                (*cont)++;
            }
        }
    }
    original->esq = de_morgan(original->esq, cont);
    original->dir = de_morgan(original->dir, cont);
    return original;
}
// função que remove a dupla negação
arvore remover_dupla_negacao(arvore original, int *cont)
{
    if (original == NULL)
    {
        return NULL;
    }
    if (original->esq != NULL)
    {
        if (original->info == '!' && original->esq->info == '!')
        {
            arvore neto = original->esq->esq;
            free(original->esq);
            free(original);
            *cont = 1;
            return neto;
        }
    }
    original->esq = remover_dupla_negacao(original->esq, cont);
    original->dir = remover_dupla_negacao(original->dir, cont);
    return original;
}
// função que libera a árvore
void liberar_arvore(arvore arvore)
{
    if (arvore == NULL)
        return;
    liberar_arvore(arvore->esq);
    liberar_arvore(arvore->dir);
    free(arvore);
}
// função que printa a árvore recursivamente da mesma forma que estava antes, de uma forma infixa
void printar_arvore(arvore original)
{
    if (original == NULL)
        return;
    if (original->info == '&' || original->info == '|')
    {
        printf("(");
        printar_arvore(original->esq);
        printf("%c", original->info);
        printar_arvore(original->dir);
        printf(")");
    }
    else if (original->info == '!')
    {
        printf("%c", original->info);
        printar_arvore(original->esq);
    }
    else
        printf("%c", original->info);
}
// função que altera !T para F ou !F para T
arvore troca_negacao_bool(arvore original, int *cont)
{
    if (original == NULL)
        return NULL;
    if (original->info == '!' && original->esq != NULL)
        if (original->esq->info == 'T' || original->esq->info == 'F')
        {
            arvore filho = original->esq;
            original->info = (original->esq->info == 'T') ? 'F' : 'T';
            original->esq = filho->esq;
            free(filho); // libera o !
        }
    original->dir = troca_negacao_bool(original->dir, cont);
    original->esq = troca_negacao_bool(original->esq, cont);
    return original;
}
// função que devolve se duas subárvores possuem equivalência
int equivalencia(arvore exp1, arvore exp2)
{
    if (exp1 == NULL && exp2 == NULL)
        return 1;
    if (exp1 == NULL || exp2 == NULL)
        return 0;
    if (exp1->info != exp2->info)
        return 0;
    if (exp1->info == '&' || exp1->info == '|')
        if ((equivalencia(exp1->esq, exp2->esq) && equivalencia(exp1->dir, exp2->dir)) || // como os operadores & e | não precisam que os termos venham na mesma ordem
            (equivalencia(exp1->esq, exp2->dir) && equivalencia(exp1->dir, exp2->esq)))   // temos que verificar se os termos são iguais na mesma ordem ou em ordem diferentes
            return 1;
    return (equivalencia(exp1->esq, exp2->esq) && equivalencia(exp1->dir, exp2->dir)); // se é um termo normal(sem ser de expressão), verificamos o resto, normalmente.
}
// função que trata a operação & recursivamente
arvore operacao_e(arvore original, int *cont)
{
    if (original == NULL)
        return NULL;
    original->dir = operacao_e(original->dir, cont); // começamos aqui a recursão, para primeiro alterar os termos lá de baixo
    original->esq = operacao_e(original->esq, cont);
    if (original->info == '&')
    {
        if (equivalencia(original->esq, original->dir))
        {
            arvore nova = original->esq;
            liberar_arvore(original->dir);
            free(original);
            (*cont)++;
            return nova;
        }
        if (original->esq->info == 'T')
        {
            arvore nova = original->dir;
            free(original->esq);
            free(original);
            (*cont)++;
            return nova;
        }
        if (original->dir->info == 'T')
        {
            arvore nova = original->esq;
            free(original->dir);
            free(original);
            (*cont)++;
            return nova;
        }
        if (original->esq->info == 'F' || original->dir->info == 'F')
        {
            arvore nova = conectar_novo_no('F');
            liberar_arvore(original->dir);
            liberar_arvore(original->esq);
            free(original);
            (*cont)++;
            return nova;
        }
        if (original->dir->info == 'F')
        {
            arvore nova = original->dir;
            liberar_arvore(original->esq);
            free(original);
            (*cont)++;
            return nova;
        }
    }

    return original;
}
// função recursiva que realiza as operações de |
arvore operacao_ou(arvore original, int *cont)
{
    if (original == NULL)
        return NULL;
    original->esq = operacao_ou(original->esq, cont); // chamamos a recursão aqui, para alterar a árvore de baixo para cima.
    original->dir = operacao_ou(original->dir, cont);
    if (original->info == '|')
    {
        if (equivalencia(original->esq, original->dir))
        {
            arvore nova = original->esq;
            liberar_arvore(original->dir);
            free(original);
            (*cont)++;
            return nova;
        }
        if (original->esq->info == 'T' || original->dir->info == 'T')
        {
            arvore nova = conectar_novo_no('T');
            liberar_arvore(original->esq);
            liberar_arvore(original->dir);
            free(original);
            (*cont)++;
            return nova;
        }
        if (original->esq->info == 'F')
        {
            arvore nova = original->dir;
            liberar_arvore(original->esq);
            free(original);
            (*cont)++;
            return nova;
        }
        if (original->dir->info == 'F')
        {
            arvore nova = original->esq;
            free(original->dir);
            free(original);
            (*cont)++;
            return nova;
        }
    }
    return original;
}
// função que realiza as simplificações de Morgan, a segunda linha da saída
arvore primeira_simplificacao(arvore original)
{
    // variável responsável por saber se em determinado laço, houve trocas
    int cont;
    do
    {
        cont = 0;
        original = de_morgan(original, &cont);
        original = remover_dupla_negacao(original, &cont);
    } while (cont > 0);
    printar_arvore(original);
    printf("\n");
    return original;
}
arvore ultima_simplificacao(arvore original)
{
    // variável responsável por saber se em determinado laço, houve trocas
    int cont;
    do
    {
        cont = 0;
        original = troca_negacao_bool(original, &cont);
        original = operacao_e(original, &cont);
        original = operacao_ou(original, &cont);

    } while (cont > 0);
    printar_arvore(original);
    printf("\n");
    return original;
}

int main()
{
    arvore original;
    original = criar_galho();
    printar_arvore(original);
    printf("\n");
    original = primeira_simplificacao(original);
    original = ultima_simplificacao(original);
    liberar_arvore(original);
    return 0;
}