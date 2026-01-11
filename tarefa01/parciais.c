#include <stdio.h>

void ler_sequencia(int vetor[], int len){
    for (int i = 0; i < len; i++)
        scanf("%d" , & vetor[i]);
}

void soma_parcial(int vetor[], int len){
    int soma = 0, numero_antigo;
    for (int i = 0; i < len; i++ ){
        numero_antigo = vetor[i];
        vetor[i] = soma + numero_antigo;
        soma += numero_antigo;
    }

}

void inverte(int vetor[], int vetor_inverso[], int len){
    for (int i = 0; i < len; i++)
       vetor_inverso[i] = vetor[len - i -1]; 
}
void print_inverso(int vetor[], int len){
    for (int i = 0; i< len; i++){
        printf("%d ", vetor[i]);


    }
}


int main(){
    int vetor[1000], len, vetor_inverso[1000];
    scanf("%d", &len);
    ler_sequencia(vetor, len);
    soma_parcial(vetor, len);
    inverte(vetor, vetor_inverso, len);
    print_inverso(vetor_inverso, len);
    printf("\n");
    return 0;
}