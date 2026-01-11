#include <stdio.h>
#include <string.h>
#define MAX 401


int contagem_diferentes(char palavra[], int num_diferentes, int esq, int dir){ //função recursiva que retorna o número de caracteres diferentes
    if (esq >= dir)
        return num_diferentes;
    
    else if (palavra[esq] != palavra[dir])
        return contagem_diferentes(palavra, num_diferentes + 2, esq + 1, dir -1);
    
    return contagem_diferentes(palavra, num_diferentes, esq + 1, dir - 1);
}

int len_palavra(char palavra[]){ //função que retoma o número correto do len, pois ao utilizar a função fgets, ele declara ao final da string um '/n', o que faz que o len seja errado
    int len_palavra;
    len_palavra = strlen(palavra);
    if (palavra[len_palavra - 1] == '\n')
        palavra[len_palavra - 1] = '\0';
    return strlen(palavra);

}



int main(){
    int n;
    char palavra[MAX];
    scanf("%d ", &n);
    fgets(palavra, MAX, stdin);
    if (contagem_diferentes(palavra, 0, 0, len_palavra(palavra) - 1) <= n)
        printf("sim\n");
    else
        printf("nao\n");
   
    return 0;
}