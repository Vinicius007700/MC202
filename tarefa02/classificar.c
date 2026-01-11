#include <stdio.h>
#define max_pacientes 100
#define max_carac 31
void add_nomes(char nomes[][max_carac], int n){
    //função que adiciona os nomes a um vetor de vetor na forma char
    char letra;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < max_carac; j++){
            scanf("%c", &letra);
            if (letra == '\n'){
                nomes[i][j] = '\0';
                break;
            }
            nomes[i][j] = letra;
}

}
void printar_respostas(char nomes[][max_carac], int i){
    //função que dado um i(indice), imprime todas as letras de uma determinada palavra, pois estão no vetor de um vetor(em char)
    for (int n = 0; nomes[i][n]!='\0'; n++)
        printf("%c", nomes[i][n]);
    printf("\n");
    
    

}

void procura_homonimos(char nomes[][max_carac], char homonimo[max_carac], int n){
    for (int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++){
            if (nomes[i][j] != homonimo[j+10]) {// j + 10, pois a palavra homonimo + o espaço, tem 9 caracteres, e eu quero analisar o próximo(que é 10)
                if (nomes[i][j] == '_' && homonimo[j+10] == '\n')
                    printar_respostas(nomes, i);
                else
                    break;
    }
        }
}
int procura_inicio_sobrenome(char nomes[][max_carac], int indice){
    //função que procura o primeiro _, para encontrar em qual índice começa o sobrenome
    for (int i = 0; i < max_carac; i++)
        if (nomes[indice][i] == '_')
            return i + 1;

    return 0; 
}



void procura_parentes(char nomes[][max_carac], char homonimo[max_carac], int n){
    int l, j, comeco;
    for (int i = 0; i < n; i++){
        comeco = procura_inicio_sobrenome(nomes, i);
        for(j = comeco, l = 9; j < max_carac; j++, l++){ // l começa igual a 9, pois a palavra parentes + o espaço tem 8 caracteres,e eu quero analisar o próximo(que é 10)
            if (nomes[i][j] == '\0' && homonimo[l] == '\n')
                printar_respostas(nomes, i);
            else if (nomes[i][j] != homonimo[l]){
                break;
            }
            
        }
    }
}


int main(){
    int n;
    char nomes[max_pacientes][max_carac], opcao[max_carac];
    scanf("%d ", &n);
    add_nomes(nomes, n);
    fgets(opcao, max_carac, stdin);
    if (opcao[0] == 'h')
        procura_homonimos(nomes, opcao, n);
    else
        procura_parentes(nomes, opcao, n);
    

    return 0;
}