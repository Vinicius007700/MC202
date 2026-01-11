#include <stdio.h>
void ler_matriz(int matriz[][100], int num_linhas, int num_colunas){
    for (int i = 0; i < num_linhas; i++)
        for (int j = 0; j < num_colunas; j++)
                scanf("%d" , &matriz[i][j]);
}

int verifica_se_e_menor_linha(int pos_linha, int pos_coluna, int matriz[][100], int num_linhas, int num_colunas){
    for (int i = 0; i < num_colunas; i++)
        if (i != pos_coluna)
            if (matriz[pos_linha][pos_coluna] >= matriz[pos_linha][i])
                return 0;
    return 1;
}


int verifica_se_e_maior_coluna(int pos_linha, int pos_coluna, int matriz[][100], int num_linhas, int num_colunas){
    for (int i =0; i < num_linhas; i++)
        if (i != pos_linha)
            if (matriz[pos_linha][pos_coluna] <= matriz[i][pos_coluna])
                return 0;
    return 1;
}


    


int main(){
    int num_linhas, num_colunas, matriz[100][100], bool = 0;
    scanf("%d %d", &num_linhas, &num_colunas);
    ler_matriz(matriz, num_linhas, num_colunas);
    for (int i = 0; i < num_linhas; i++)
        for (int j = 0; j < num_colunas; j++)
            if (verifica_se_e_maior_coluna(i, j, matriz, num_linhas, num_colunas) && verifica_se_e_menor_linha(i, j, matriz, num_linhas, num_colunas)){
                printf("(%d, %d) eh ponto de sela com valor %d\n", i, j, matriz[i][j]);
                bool = 1;
                break;
             }
    if (! bool)
        printf("nao existe ponto de sela");
    
    return 0;
}