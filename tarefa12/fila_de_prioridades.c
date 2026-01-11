#include "centros.h"

p_fp criar_fprio(int tam)
{
    p_fp fprio = malloc(sizeof(struct FP));
    fprio->v = malloc(tam * sizeof(struct item));
    fprio->n = 0;
    fprio->tamanho = tam;
    return fprio;
}
void troca_itens(item *a, item *b)
{
    item temp = *a;
    *a = *b;
    *b = temp;
}
void desce_no_heap(p_fp fprio, int k)
{
    int menor_filho;
    if (F_ESQ(k) < fprio->n)
    {
        menor_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n &&
            fprio->v[F_ESQ(k)].dist > fprio->v[F_DIR(k)].dist)
            menor_filho = F_DIR(k);
        if (fprio->v[k].dist > fprio->v[menor_filho].dist)
        {
            troca_itens(&fprio->v[k], &fprio->v[menor_filho]);
            desce_no_heap(fprio, menor_filho);
        }
    }
}
int extrai_minimo(p_fp fprio)
{
    item item = fprio->v[0];
    troca_itens(&fprio->v[0], &fprio->v[fprio->n - 1]);
    fprio->n--;
    desce_no_heap(fprio, 0);
    return item.v;
}



void sobe_no_heap(p_fp fprio, int k)
{
    if (k > 0 && fprio->v[PAI(k)].dist > fprio->v[k].dist)
    {
        troca_itens(&fprio->v[k], &fprio->v[PAI(k)]);
        sobe_no_heap(fprio, PAI(k));
    }
}

//Função que insere um elemento na fila de prioridades
void insere(p_fp fprio, item item)
{
    fprio->v[fprio->n] = item;
    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1);
}
//Função que verifica se uma fila de prioridades está vazia
int vazia(p_fp fprio)
{
    return fprio->n == 0;
}

void diminui_prioridade(p_fp fprio, int vertice, int nova_dist)
{
    int pos;
    for (int i = 0; i < fprio->n; i++)
    {
        if (fprio->v[i].v == vertice)
        {
            pos = i;
            break;
        }
    }
    if (nova_dist < fprio->v[pos].dist)
    {
        fprio->v[pos].dist = nova_dist;
        sobe_no_heap(fprio, pos);
    }
}

