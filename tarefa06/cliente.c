#include <stdio.h>
#include <string.h>
#include "cobra.h"

int main()
{
    // variável que irá guardar o campo de jogo
    char **matriz;
    cabeca cabeca;
    cobra corpo_cobra;
    char comando[6];
    int linha, coluna, linha_inicial_cobra, col_inicial_cobra, num_linhas, num_colunas;
    // variável que será responsável por ver se deu GAME OVER, quando valer 0(False)
    int win = 1;
    scanf("%s %d %d", comando, &num_linhas, &num_colunas);
    scanf("%s %d %d", comando, &linha_inicial_cobra, &col_inicial_cobra);
    matriz = criar_matriz(linha_inicial_cobra, col_inicial_cobra, num_linhas, num_colunas);
    corpo_cobra = inicializar_corpo_cobra(linha_inicial_cobra, col_inicial_cobra);
    cabeca = inicializar_cabeca(corpo_cobra);
    while (cabeca->len_cobra != num_linhas * num_colunas)
    {
        scanf("%s", comando);
        if (strcmp(comando, "FRUTA") == 0)
        {
            scanf("%d %d", &linha, &coluna);
            matriz[linha][coluna] = '*';
        }
        else if (!movimentacao_tabuleiro(comando[0], matriz, corpo_cobra, cabeca, num_linhas, num_colunas))
        {
            printf("GAME OVER\n");
            win = 0;
            break;
        }

        print_tabuleiro(matriz, num_linhas, num_colunas);
    }
    if (win)
        printf("YOU WIN\n");
    free_corpo_cobra(cabeca);
    free_matriz(matriz, num_linhas);
    return 0;
}
