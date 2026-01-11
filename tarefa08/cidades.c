#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cidades.h"
#define CENTRO(len) len / 2
#define num_coordenadas 4
#define interno -1
#define raiz -2
#define tamanho_max_nome 10


/*Função que retorna qual coordenada estará determinado ponto*/
int encontrar_coordenadas(arvore original, int pos_x, int pos_y)
{

    if (pos_y > original->centro_y)
    {
        if (pos_x < original->centro_x)
            return NO;
        else
            return NE;
    }
    else
    {
        if (pos_x < original->centro_x)
            return SO;
        else
            return SE;
    }
}

/*Função que cria a árvore pela primeira vez*/
arvore inicializa_arvore(int tamanho)
{
    arvore nova_arvore = malloc(sizeof(struct arvore));
    nova_arvore->pos_x = nova_arvore->pos_y = raiz; /*tratamos a raiz como diferente para que não haja problemas na hora de remoção*/
    nova_arvore->nome[0] = 'i';                     /*i de interno*/
    for (int i = 0; i < num_coordenadas; i++)
        nova_arvore->filhos[i] = NULL;
    nova_arvore->centro_x = nova_arvore->centro_y = CENTRO(tamanho);
    return nova_arvore; 
}
/*Função que cria um nó interno, com as posições do novo centro*/
arvore cria_novo_interno(arvore original, enum coordenadas coord)
{
    double cont, novo_centro_x, novo_centro_y;
    arvore novo_interno = malloc(sizeof(struct arvore));
    novo_interno->pos_x = novo_interno->pos_y = interno;
    novo_interno->nome[0] = 'i'; /*i de interno*/
    for (int i = 0; i < num_coordenadas; i++)
        novo_interno->filhos[i] = NULL;
    if (coord == NO || coord == NE)
    {
        novo_centro_y = (1.5) * (original->centro_y); /*1.5->significa essa operação dado um número x ---(x+0,5*x)*/
        cont = (coord == NE) ? +1 : -1;
        novo_centro_x = original->centro_x + cont * (original->centro_x / 2); /*Esta operação é a mesma da linha 54, */
    } /*a sua única diferença é que não sabemos se será x + 0,5x ou x - 0,5x, para resolver o problema, temos a variável cont*/
    else
    {
        novo_centro_y = (0.5) * original->centro_y; /*0.5 -> significa a operação (x - 0,5x). Raciocínio homólogo da linha 54*/
        cont = (coord == SE) ? +1 : -1;
        novo_centro_x = original->centro_x + cont * (original->centro_x / 2); // Mesmo raciocínio da linha 54
    }
    novo_interno->centro_x = novo_centro_x;
    novo_interno->centro_y = novo_centro_y;
    original->filhos[coord] = novo_interno;
    return original;
}
/*Função que insere uma cidade*/
arvore inserir_cidade(enum coordenadas coord, arvore original, int pos_x, int pos_y, char *nome)
{
    arvore nova = malloc(sizeof(struct arvore));
    nova->pos_x = pos_x;
    nova->pos_y = pos_y;
    strncpy(nova->nome, nome, tamanho_max_nome); /*Adicionando o nome da cidade*/
    for (int i = 0; i < num_coordenadas; i++)
    {
        nova->filhos[i] = NULL;
    }
    original->filhos[coord] = nova;

    return original;
}

/*Função que é chamada quando o cliente utiliza a função de inserção*/
arvore inserir_elemento(arvore original, int pos_x, int pos_y, char *nome)
{
    int coord = encontrar_coordenadas(original, pos_x, pos_y);
    if (original->filhos[coord] == NULL) /* se não há nenhum elemento nesta região, podemos inserir a cidade tranquilamente*/
        original = inserir_cidade(coord, original, pos_x, pos_y, nome);
    else if (original->filhos[coord]->pos_x == interno) /*se o proximo filho é um nó interno, nós vamos ter que usar a
                                recursão para ir até este outro nó até encontrar algum lugar propício para a inserção*/
    {
        original->filhos[coord] = inserir_elemento(original->filhos[coord], pos_x, pos_y, nome);
    }
    else /*se já há algum elemento nesta região, devemos dividi-la, em mais quadrantes*/
    {
        arvore aux = original->filhos[coord]; /*apontamos para o elemento que já estava antes*/
        original = cria_novo_interno(original, coord);
        original->filhos[coord] = inserir_elemento(original->filhos[coord], aux->pos_x, aux->pos_y, aux->nome);
        original->filhos[coord] = inserir_elemento(original->filhos[coord], pos_x, pos_y, nome); /*vamos inserir os dois elementos que estavam */
        free(aux); /*liberamos o aux para evitar vazamentos de memória*/                         /*  na mesma posição sendo filhos do mesmo nó interno */
    }
    return original;
}

arvore remocao(arvore original, int pos_x, int pos_y, char nome[tamanho_max_nome])
{
    int cont = 0, ultimo;
    int coord = encontrar_coordenadas(original, pos_x, pos_y);
    if (original->filhos[coord] == NULL)
        return original;
    if (original->filhos[coord]->pos_x == interno) /*Se o nó que estamos analisando é um nó interno, continuaremos a nossa busca*/
        original->filhos[coord] = remocao(original->filhos[coord], pos_x, pos_y, nome);
    else if (original->filhos[coord]->pos_x == pos_x && original->filhos[coord]->pos_y == pos_y) /*Quando nós encontramos a cidade*/
    {
        strncpy(nome, original->filhos[coord]->nome, tamanho_max_nome);
        free(original->filhos[coord]);
        original->filhos[coord] = NULL;
        for (int i = 0; i < num_coordenadas; i++)
        {
            if (original->filhos[i] != NULL)
            {
                cont += 1; /*Temos que verificar quantos nós ocupados o nó que removemos está utilizando*/
                ultimo = i;
            }
        }
        if (cont == 0 && original->pos_x != raiz) /*Se o nó interno não aponta para nenhuma cidade. */
        {                                         /* temos que remover este nó, também. */
            free(original);                       /* Exceto que seja uma raíz, pois não podemos removê-la*/
            return NULL;
        }
        else if (cont == 1 && original->pos_x != raiz) /*Se o nó interno para para uma cidade, temos que remover este nó e retornar esta única cidade, */
        {                                              /* para que nós não percamos esta informação*/
            arvore temp = original->filhos[ultimo];
            free(original);
            return temp;
        }
    }
    return original;
}
/*Função recursiva que busca por uma cidade*/
int busca_por_ponto(arvore original, int pos_x, int pos_y, char * nome)
{
    int coord = encontrar_coordenadas(original, pos_x, pos_y);
    if (original->filhos[coord] == NULL) /*Quando não podemos usar a recursão para buscar mais, significa que determinado ponto está vazio*/
    {
        return 0;
    }
    else if (original->filhos[coord]->pos_x == interno) /*Se nós encontrarmos um nó interno, temos que usar a */
        return busca_por_ponto(original->filhos[coord], pos_x, pos_y, nome); /*recursão, para olhar a partir deste ponto*/
    else if (original->filhos[coord]->pos_x == pos_x && original->filhos[coord]->pos_y == pos_y)
    {
        strncpy(nome, original->filhos[coord]->nome, tamanho_max_nome);
        return 1;
    }
    return 0;
    
}
//Função que busca elementos que estão perto dentro de uma região e os armazena em um vetor
void busca_por_regiao(arvore original, int pos_x, int pos_y, int dist, char ** vetor_saida, int * num_elementos_vetor) {
    if (original == NULL) {
        return; 
    }
    if (original->pos_x >= 0) {  
        double distancia = sqrt(pow(original->pos_x - pos_x, 2) + pow(original->pos_y - pos_y, 2));/*Distância entre 2 pontos*/
        if (distancia <= dist) {
            vetor_saida[*num_elementos_vetor] = (char *)malloc(tamanho_max_nome * sizeof(char));
            strncpy(vetor_saida[*num_elementos_vetor], original->nome, tamanho_max_nome);
            (*num_elementos_vetor)++;
        }
        return;  
    }
    int centro_x = original->centro_x;
    int centro_y = original->centro_y;
    //Estaremos neste caso, apenas se seja um nó interno,
    // Verificando para o caso NO
    if (pos_x - dist < centro_x && pos_y + dist > centro_y) { //Nós tratamos o ponto como se fosse uma circunferência, 
        if (original->filhos[NO] != NULL) { // e verificamos primeiro no ponto mais a esquerda, depois o ponto mais acima,
            busca_por_regiao(original->filhos[NO], pos_x, pos_y, dist, vetor_saida, num_elementos_vetor); //porque, se esses pontos estiverem, dentro das condições
                                                                        //do if na linha 186, este ponto poderá estar na região NO 
        }
    }

    // Verificando para NE
    if (pos_x + dist > centro_x && pos_y + dist > centro_y) { //Agora, usamos o mesmo raciocínio para o caso do NO, apenas
        if (original->filhos[NE] != NULL) { //adaptando para os outros pontos cardeais;
            busca_por_regiao(original->filhos[NE], pos_x, pos_y, dist, vetor_saida, num_elementos_vetor);
        }
    }
    
    // Verificando para SO
    if (pos_x - dist < centro_x && pos_y - dist < centro_y) {
        if (original->filhos[SO] != NULL) {
            busca_por_regiao(original->filhos[SO], pos_x, pos_y, dist, vetor_saida, num_elementos_vetor);
        }
    }

    // Verificando para SE
    if (pos_x + dist > centro_x && pos_y - dist < centro_y) {
        if (original->filhos[SE] != NULL) {
            busca_por_regiao(original->filhos[SE], pos_x, pos_y, dist, vetor_saida, num_elementos_vetor);
        }
    }
}
/*Função recursiva que libera a árvore*/
void liberar_arvore(arvore original)
{
    for (int i = 0; i < num_coordenadas; i++)
    {
        if (original->filhos[i] != NULL)
            liberar_arvore(original->filhos[i]);
    }
    if (original != NULL)
    {
        free(original);
    }
}

void printar_cidades_do_vetor(char ** vetor_saida, int num_elementos_vetor, int dist, int pos_x, int pos_y){
    printf("Cidades a distancia %d de (%d,%d):", dist, pos_x, pos_y);
    for(int i = 0; i < num_elementos_vetor; i++){
        printf("%s ", vetor_saida[i]);
    }
    printf("\n");
}
// Função que libera o vetor que foi armazenado na função de busca_por_região
void liberar_vetor(char ** vetor_saida, int num_elementos_vetor){
    for(int i = 0; i < num_elementos_vetor; i++)
        free(vetor_saida[i]);

}