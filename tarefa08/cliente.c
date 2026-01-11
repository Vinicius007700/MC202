#include <stdio.h>
#include "cidades.h"
#define tamanho_max_nome 10
#define MAX_CIDADES 1000
#define FIM 0
#define CONTINUE 1
int main()
{
    arvore arvore;
    int tamanho, pos_x, pos_y, dist, 
    /* Variável que é responsável pelo programa parar ou não */
    condicao_de_parada  = CONTINUE ;
    char entrada, * vetor_saida[MAX_CIDADES];
    char nome[tamanho_max_nome], saida[tamanho_max_nome];
    scanf("%d", &tamanho);
    arvore = inicializa_arvore(tamanho);
    while (condicao_de_parada != FIM)
    {
        scanf(" %c", &entrada);
        if (entrada == 'i')
        {
            scanf("%d %d %s", &pos_x, &pos_y, nome);
            arvore = inserir_elemento(arvore, pos_x, pos_y, nome);
            printf("Cidade %s inserida no ponto (%d,%d).\n", nome, pos_x, pos_y); 
        }
        else if (entrada == 'b')
        {
            scanf("%d %d", &pos_x, &pos_y);
            if(busca_por_ponto(arvore, pos_x, pos_y, saida))
                printf("Cidade %s encontrada no ponto (%d,%d).\n", saida, pos_x, pos_y);
            else
                printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", pos_x, pos_y);
        }
        else if (entrada == 'o')
        {
            int num_elementos_vetor = 0;
            scanf("%d %d %d", &pos_x, &pos_y, &dist);
            busca_por_regiao(arvore, pos_x, pos_y, dist, vetor_saida, &num_elementos_vetor);
            printar_cidades_do_vetor(vetor_saida, num_elementos_vetor, dist, pos_x, pos_y);
            liberar_vetor(vetor_saida, num_elementos_vetor);
        }
        else if (entrada == 'r'){
            scanf("%d %d", &pos_x, &pos_y);
            arvore = remocao(arvore, pos_x, pos_y, saida);
            printf("Cidade %s removida do ponto (%d,%d).\n", saida, pos_x, pos_y);
           
        }
        else if (entrada == 's')
        {
            condicao_de_parada = FIM;
        }
    }
    printf("Sistema encerrado.\n");
    liberar_arvore(arvore);
    return 0;
}