#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000
typedef struct preparo{
    double * sem_normalizar, * normalizar, * vetorial;
}preparo;
void ler_d_n(int * d, int * n){
    scanf("%d %d", d, n);
}
void inicializar_vetor(double * valores, int n){
    for (int i = 0; i < n; i++)
        valores[i] = 0;
}
void metodo_sem_normalizar(double * valores, double * lista_de_numeros, int n, int d){
    for (int i = 0; i < n * d; i++)
            valores[i % d] += lista_de_numeros[i] / n;
        }
void armazenar_entrada(double * vetor, int n, int d){ //função que armazena em um vetor os números que serão dados na entrada.
    for (int i = 0; i < n * d; i++) //n*d, pois é o número total de elementos que cada lista_de_numeros terá, não estarei resolvendo por matriz.
            scanf("%lf", &vetor[i]);
}
void calcular_media(double * valores, int n){
    for (int i = 0; i <= n; i++)
        valores[i] = valores[i] / n;
}
void normarlizar(double * valores, double * lista_de_numeros, int n, int d, double min, double max, int inicio){
    if (max != min){
        for (int i = inicio; i < n * d; i+=d){ //n*d, pois é o número total de elementos que cada lista_de_numeros terá, não estarei resolvendo por matriz.
            valores[inicio] += (2*(lista_de_numeros[i] - min) / (max - min)) - 1;
        }
    }
    else{
        valores[inicio] = 0;
    }
    valores[inicio]= valores[inicio]/n; 
}
void metodo_normalizar(double * valores, double * lista_de_numeros, int n, int d){
    double max, min;
    int cont = 0;
    for (int j = 0; j <= n; j++){
        cont = 0; 
        for (int i = j; i < n*d; i+=d){
            if (!cont){
                min = lista_de_numeros[i];
                max = lista_de_numeros[i];
                cont++;
            }
            else if (lista_de_numeros[i] > max)
                max = lista_de_numeros[i];
            else if (lista_de_numeros[i] < min)
                min = lista_de_numeros[i]; 
            
        }
        normarlizar(valores, lista_de_numeros, n, d, min, max, j);
    }
}
void norma_euclidiana(double * valores, double * lista_de_numeros, int n, int d){
    double norma;
    for (int i = 0; i < n *d; i++){
        norma = 0;
        for (int j = i - i % d; j < i - i % d + d; j++) // o j é inicializado como i - i % d, para que seja possível que nós consigamos o índice do termo na mesma linha, e assim, percorrer todos os números da mesma para que seja possível calcular a norma
            norma += lista_de_numeros[j] * lista_de_numeros[j];
        valores[i % d] += lista_de_numeros[i] / (sqrt(norma) * n) ;
        }
}
void printar_respostas(double * valores, int d){
    for (int i = 0; i < d; i++)
        printf("%.3f ", valores[i]);
    printf("\n");  
}
void tratamento_de_dados(double *sem_normalizar, double * normalizar, double * vetorial, double * lista_de_numeros, int n, int d){ // função responsável por chamar as outras funções responsáveis pelos cálculos necessários
    metodo_sem_normalizar(sem_normalizar, lista_de_numeros, n, d);
    metodo_normalizar(normalizar, lista_de_numeros, n, d);
    norma_euclidiana(vetorial, lista_de_numeros, n, d);
}
void printar_tudo(double *sem_normalizar, double * normalizar, double * vetorial, int d){ // função responsável pelo print da resposta
    printf("nenhum: ");
    printar_respostas(sem_normalizar, d);
    printf("janela: ");
    printar_respostas(normalizar, d);
    printf("normal: ");
    printar_respostas(vetorial, d);
}
void inicializar_tudo(double *sem_normalizar, double * normalizar, double * vetorial, int n){
    inicializar_vetor(sem_normalizar, n);
    inicializar_vetor(normalizar, n);
    inicializar_vetor(vetorial, n);
}
void liberar_memoria(preparo *respostas, double * lista_de_numeros) {
    free(respostas->normalizar);
    free(respostas->sem_normalizar);
    free(respostas->vetorial);
    free(lista_de_numeros);
    free(respostas);
}
void alocar_memoria(preparo ** respostas, double ** lista_de_numeros){
    * respostas = (preparo *)malloc(sizeof(preparo));
    * lista_de_numeros = (double *)malloc(MAX * MAX * sizeof(* lista_de_numeros));
    (*respostas)->sem_normalizar = (double *)malloc(MAX * sizeof((*respostas)->sem_normalizar));
    (*respostas)->normalizar = (double *)malloc(MAX * sizeof((*respostas)->normalizar));
    (*respostas)->vetorial = (double *)malloc(MAX * sizeof((*respostas)->vetorial));
    
    if ((*respostas)->sem_normalizar == NULL || (*respostas)->normalizar == NULL || (*respostas)->vetorial == NULL || *lista_de_numeros == NULL || * respostas == NULL) {
        printf("Não há memória suficiente");
        exit(1);
    }
}
int main(){
    preparo *respostas;
    int d, n;
    double * lista_de_numeros;
    alocar_memoria(&respostas,  &lista_de_numeros);
    ler_d_n(&d, &n);
    armazenar_entrada(lista_de_numeros, n, d);
    inicializar_tudo(respostas->sem_normalizar, respostas->normalizar, respostas->vetorial, n);
    tratamento_de_dados(respostas->sem_normalizar, respostas->normalizar, respostas->vetorial,lista_de_numeros, n, d);
    printar_tudo(respostas->sem_normalizar, respostas->normalizar, respostas->vetorial, d);
    liberar_memoria(respostas, lista_de_numeros);
    return 0;
}
