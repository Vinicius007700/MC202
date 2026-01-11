#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 15
#define MAX_INICIO 8
#define MAX_LACUNAS 10000
typedef struct vetor *p_vetor;
typedef struct lacunas *l_lacunas;
typedef struct espacos_utilizados *espacos_utilizados;
struct vetor { 
    int *dados;
    int n;
};
struct lacunas{
    int * comeco;
    int * final;
    int * tamanho;
    int n;
};
struct espacos_utilizados{
    int * comeco;
    int * final;
    int * tamanho;
    int n;
};
p_vetor criar_vetor(){
    p_vetor v;
    v = malloc(sizeof(struct vetor));
    if (v == NULL) {
        perror("Erro ao alocar memória para vetor");
        exit(EXIT_FAILURE);
    }
    v -> dados = malloc(MAX_INICIO * sizeof(int));
    if (v->dados == NULL) {
        perror("Erro ao alocar memória para dados do vetor");
        free(v);
        exit(EXIT_FAILURE);
    }
    v -> n = MAX_INICIO;
    return v;
}
l_lacunas criar_lacunas_iniciais(){
    l_lacunas l;
    l = malloc(sizeof(struct lacunas));
    if (l == NULL) {
        perror("Erro ao alocar memória para lacunas");
        exit(EXIT_FAILURE);
    }
    l -> comeco = malloc(MAX_LACUNAS * sizeof(int));
    l -> final = malloc(MAX_LACUNAS * sizeof(int));
    l -> tamanho = malloc(MAX_LACUNAS * sizeof(int));
    if (l->comeco == NULL || l->final == NULL || l->tamanho == NULL) {
        perror("Erro ao alocar memória para lacunas");
        free(l->comeco);
        free(l->final);
        free(l->tamanho);
        free(l);
        exit(EXIT_FAILURE);
    }
    l->n = 0;
    return l;
}
espacos_utilizados criar_espacos_utilizados(){
    espacos_utilizados espacos_utilizados;
    espacos_utilizados = malloc(sizeof(struct espacos_utilizados));
    if (espacos_utilizados == NULL){
        perror("Erro ao alocar memória para espaços utilizados");
        exit(EXIT_FAILURE);
    }
    espacos_utilizados -> comeco = malloc(MAX_LACUNAS * sizeof(int));
    espacos_utilizados ->final = malloc(MAX_LACUNAS * sizeof(int));
    espacos_utilizados -> tamanho = malloc(MAX_LACUNAS *sizeof(int));
    if (espacos_utilizados->comeco == NULL || 
        espacos_utilizados->final == NULL || 
        espacos_utilizados->tamanho == NULL) {
            perror("Erro ao alocar memória para espaços utilizados");
            free(espacos_utilizados->comeco);
            free(espacos_utilizados->final);
            free(espacos_utilizados->tamanho);
            free(espacos_utilizados);
            exit(EXIT_FAILURE);
    }
    espacos_utilizados -> n = 0;
    return espacos_utilizados;
}
void retroceder_espacos_utilizados_1_posicao(espacos_utilizados espacos_utilizados, p_vetor v, l_lacunas l, int posicao_troca){
    for (int i = posicao_troca; // função responsável por encolher a informação de espaços utilizados, e assim passar as informações 1 posição para a esquerda, para apagar a informação que foi liberada
        i < espacos_utilizados->n - 1; 
        i++){
            espacos_utilizados->comeco[i] = espacos_utilizados->comeco[i+1];
            espacos_utilizados->final[i] = espacos_utilizados -> final[i+1];
            espacos_utilizados->tamanho[i] = espacos_utilizados -> tamanho[i+1];
    }
    espacos_utilizados->n --;
}
int posicao_de_adicionar(espacos_utilizados espacos_utilizados, int comeco){
    int i = 0;  //função responsável por retornar a posição que determinado dado irá ter no vetor de espacos_utilizados
    for (i = 0; i< espacos_utilizados->n; i++){
        if(espacos_utilizados -> final[i] > comeco ){
            break;
        }

    }
    return i;
}
void empurrar_espacos_preenchidos_1_posicao(espacos_utilizados espacos_utilizados, int posicao_troca){
    int subtracao = 1; // função responsável por aumentar a informação de espaços_utilizados e empurrar uma casa para a direita, todos os dados que estão há direita da posição desejada
    if (posicao_troca == 0) // para evitar acessos inválidos na memória
        subtracao = 0;
    for(int i = espacos_utilizados->n; i > posicao_troca - subtracao; i--){
        espacos_utilizados->comeco[i] = espacos_utilizados->comeco[i - 1];
        espacos_utilizados->final[i] = espacos_utilizados->final[i - 1];
        espacos_utilizados->tamanho[i] = espacos_utilizados->tamanho[i - 1];
        }
    espacos_utilizados->n ++;
   
}

void adicionar_espacos_preenchidos(espacos_utilizados espacos_utilizados, int comeco, int final){
    int posicao; // função responsável por adicionar os espaços que foram preenchidos
    posicao = posicao_de_adicionar(espacos_utilizados, comeco);
    empurrar_espacos_preenchidos_1_posicao(espacos_utilizados, posicao);    
    espacos_utilizados->final[posicao] = final;
    espacos_utilizados->comeco[posicao] = comeco;
    espacos_utilizados->tamanho[posicao] = final - comeco + 1;

}
void atualizar_lacunas(l_lacunas l, espacos_utilizados espacos_utilizados, p_vetor v){
    int  indice = 0, cont; // função responsável por atualizar as lacunas, a partir dos dados dos espaços_utilizados
    l->n = 0;
    if (espacos_utilizados->n == 0){ // se não há nenhum espaço utilizado, todas as posições representam uma única lacuna
        l->n = 1;
        l->comeco[0] = 0;
        l->final[0] = v->n - 1;
        l->tamanho[0] = l->final[0] - l->comeco[0] + 1;
    }
    else{
        if (espacos_utilizados->comeco[0] != 0){ // se o primeiro espaco_utilizado não está na primeira posição, temos que a primeira lacuna está na posição 0 do vetor até uma casa antes do primeiro espaço utilizado.
            l->comeco[indice] = 0;
            l->final[indice] = espacos_utilizados->comeco[0] - 1;
            l->tamanho[indice] = l->final[indice] - l->comeco[indice] + 1;
            indice ++; 
            l->n++;
        }
        cont = 0;
        for (indice = indice; cont<espacos_utilizados->n - 1; indice++, cont++, l->n++){
            l->comeco[indice] = espacos_utilizados->final[cont] + 1;
            l->final[indice] = espacos_utilizados->comeco[cont + 1] - 1;
            l->tamanho[indice] = l->final[indice] - l->comeco[indice] + 1;
        }
        if (espacos_utilizados->final[espacos_utilizados->n - 1] != v->n - 1){ // se o último espaco_utilizado não está na última posição do vetor, temos uma lacuna depois do último espaco_utilizado até a última posição do vetor.
            l->comeco[indice] = espacos_utilizados->final[cont] + 1;
            l->final[indice] = v->n - 1;
            l->tamanho[indice] = l->final[indice] - l->comeco[indice] + 1;
            l->n++;
        }
    


}
}
int contagem_elementos(espacos_utilizados espacos_utilizados){
    int cont = 0; //função responsável por contar quantos elementos estão sendo utilizados
    for(int i= 0; i < espacos_utilizados->n; i++)
        cont += espacos_utilizados->tamanho[i];
    return cont;
}

void bat_alloc(p_vetor v, l_lacunas l, espacos_utilizados espacos_utilizados){
    int num_adicoes, numero, verif = 0;
    int *temp, i, aux;
    scanf("%d ", &num_adicoes);
    atualizar_lacunas(l, espacos_utilizados, v);
    do{
        for (int j = 0; j < l -> n; j++){
            if (l -> tamanho[j]  >= num_adicoes + 1){
                aux = l->comeco[j]; // aux simboliza a posição que nós iremos adicionar os dados
                v->dados[aux] = num_adicoes; //adicionamos a posição o número de adições que é o primeiro número da entrada
                for (
                    i = l ->comeco[j] + 1; 
                    i < aux + num_adicoes + 1; 
                    i++
                ){
                    scanf("%d", &numero);
                    v -> dados[i] = numero;
                }

                adicionar_espacos_preenchidos(espacos_utilizados, aux , i - 1);
                verif = 1;
                printf("%d\n", aux);
                break;
            }
        }
        if (!verif){
            v -> n *= 2;
            temp = v->dados;
            v -> dados = malloc(v->n * sizeof(int));
            for (int i = 0; i < v->n / 2; i++)
                v->dados[i] = temp[i];
            
            free(temp);
            atualizar_lacunas(l, espacos_utilizados, v); 
        }
    }while(! verif);

}

void bat_free(p_vetor v, l_lacunas l, espacos_utilizados espacos_utilizados){
    int endereco, verif = 0, *temp, 
    primeiro_quarto = v->n / 4;
    scanf("%d", &endereco);
    if (v->n > 8){
        for (int i = 0; i < espacos_utilizados->n; i++){
            if (espacos_utilizados->comeco[i] == endereco){
                retroceder_espacos_utilizados_1_posicao(espacos_utilizados, v, l, i);
                break;
            }
        }
        for (int i = 0; i < espacos_utilizados->n; i++){
            if (espacos_utilizados->final[i] > primeiro_quarto){
                verif = 1;
                break;
            }
        }
        if (!verif){
            v -> n /= 2;
            temp = v->dados;
            v -> dados = malloc(v->n * sizeof(int));
            for (int i = 0; i < temp[0]; i++)
                v->dados[i] = temp[i];
            free(temp); 
        }
    }
    else{
        for (int i = 0; i < espacos_utilizados->n; i++){
            if (espacos_utilizados->comeco[i] == endereco){
                retroceder_espacos_utilizados_1_posicao(espacos_utilizados, v, l, i);
                break;
            }
        }
    }
}
void bat_print(p_vetor v, espacos_utilizados espacos_utilizados){
    int endereco;
    scanf("%d", &endereco);
    for (int i=0; i < espacos_utilizados ->n; i++){
        if (endereco == espacos_utilizados->comeco[i]){
            for (int j = endereco + 1; j < endereco + espacos_utilizados->tamanho[i]; j++ ){
                    printf("%d ", v->dados[j]);
            }
            printf("\n");
            break;
        }

    }
}
void liberar_tudo(espacos_utilizados espacos_utilizados, l_lacunas l, p_vetor v){
    free(v -> dados);
    free(espacos_utilizados->comeco);
    free(espacos_utilizados->final);
    free(espacos_utilizados->tamanho);
    free(l->comeco);
    free(l->final);
    free(l->tamanho);
    free(v);
    free(espacos_utilizados);
    free(l);
}

void bat_uso(p_vetor v, espacos_utilizados espacos_utilizados){
    printf("%d de %d\n", contagem_elementos(espacos_utilizados), v->n);
}
        
int main(){ 
    p_vetor v;
    l_lacunas l;
    espacos_utilizados espacos_utilizados;
    int n, i;
    char palavra[MAX_STR];
    v = criar_vetor();
    l = criar_lacunas_iniciais();
    espacos_utilizados = criar_espacos_utilizados();
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        scanf("%s", palavra);
        if (strcmp(palavra, "bat-alloc") == 0)
            bat_alloc(v, l, espacos_utilizados);
        else if (strcmp(palavra, "bat-free") == 0)
            bat_free(v, l, espacos_utilizados);
        else if(strcmp(palavra, "bat-print") == 0)
            bat_print(v, espacos_utilizados);
        else
            bat_uso(v, espacos_utilizados);     
    }
    liberar_tudo(espacos_utilizados, l, v);
    return 0;
}
