#include <stdio.h>
#define TAMANHO_MAXIMO_NUM 50
long long int ler_numero(){
    //função responsável por ler os números
    long long int num;
    scanf("%lld", &num);
    return num;
}
int add_lista(long long int num, long long int vetor[], int cont){
    //função responsável por adicionar ao vetor e retornar o tamanho dele
    int termo;
    do
    {
        termo = num % 10;
        num = num / 10;
        vetor[cont] =  termo;
        cont += 1;
    } while (num != 0);

    return cont;
    }

int verifica(long long int vetor[], int cont){
    //função responsável por verificar se o algarismo é capícua
    for (int i=0; i< cont/2; i++)
        if (vetor[cont - i - 1] != vetor[i])
            return 0;
    return 1;
    
}

int main(){
    long long int vetor[TAMANHO_MAXIMO_NUM], num; 
    int cont, n;
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        cont = 0;
        num = ler_numero();
        cont = add_lista(num, vetor, cont);
        if (verifica(vetor, cont)){
            printf("%lld eh capicua\n", num);}
        else
            printf("%lld nao eh capicua\n", num);

        }


 return 0;

}