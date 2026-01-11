#include <stdio.h>
#include <stdlib.h>
#define INFINITO 10000
typedef struct circuito *circuito;
struct circuito
{
    int peso, tamanho, *vetor;
};

enum estado
{
    desconhecido,
    cima,
    baixo
};
// Função que retorna se uma alavanca está para baixo ou para cima. Usamos uma string, pois se a alavanca
// for 0, teríamos problema se usássemos um int, pois não existe -0.
enum estado determina_o_estado_alavanca(char *num)
{
    if (num[0] == '-')
        return baixo;
    return cima;
}
// Função que transforma um valor +-num em apenas num, removendo o sinal; ou seja, calculando o módulo
int transforma_int(char *num)
{
    int num_inteiro = atoi(num);
    if (num_inteiro < 0)
        return -num_inteiro;
    return num_inteiro;
}
// Função que cria cada circuito separado, com as posições das alavancas e o seu peso
circuito cria_vetor_circuito_unico(int a, int peso, int tamanho)
{
    circuito circuito = malloc(sizeof(struct circuito));
    circuito->peso = peso;
    circuito->tamanho = tamanho;
    circuito->vetor = malloc(a * sizeof(int));
    for (int i = 0; i < a; i++)
    {
        circuito->vetor[i] = desconhecido;
    }
    return circuito;
}
// Função que retorna uma variável que armazena todos os circuitos separados em forma de ponteiros.
circuito *cria_vetor_com_todos_circuitos(int c, int a, int *peso_total)
{
    circuito *todos_circuitos = malloc(c * sizeof(struct circuito *));
    char num[3];
    int p, n, modulo;
    for (int i = 0; i < c; i++)
    {
        scanf("%d %d", &p, &n);
        circuito circuito_unico = cria_vetor_circuito_unico(a, p, n);
        *peso_total += p;
        for (int j = 0; j < n; j++)
        {
            scanf("%s", num);
            modulo = transforma_int(num);
            circuito_unico->vetor[modulo] = determina_o_estado_alavanca(num);
        }
        todos_circuitos[i] = circuito_unico;
    }
    return todos_circuitos;
}
// Função que cria um vetor com todas as alavancas para cima
int *todas_alavancas_para_cima(int a)
{
    int *alavancas = malloc(a * sizeof(int));
    for (int i = 0; i < a; i++)
    {
        alavancas[i] = cima;
    }
    return alavancas;
}
// Função que calcula a improbabilidade de um determinada permutação de alavancas
int calcula_improbablidade(circuito *todos_circuitos, int *estado_alavancas, int c, int a)
{
    int improbabilidade = 0;
    for (int i = 0; i < c; i++)
    {
        circuito atual = todos_circuitos[i]; // Atual é o circuito atual que estamos verificando, entre todos os circuitos
        for (int j = 0; j < a; j++)          // armazenados
        {
            if (atual->vetor[j] == estado_alavancas[j]) // Se temos uma alavanca em nossa permutação na mesma posição do circuito atual, entramos
            {                                           // somamos a improbabilidade e depois saimos, porque basta 1 alavanca igual para ser possível
                improbabilidade += atual->peso;         // ligar o circuito
                break;
            }
        }
    }
    return improbabilidade;
}
// Função que gera uma permutação com todas as alavancas para baixo
int *todas_alavancas_para_baixo(int a)
{
    int *alavancas = malloc(a * sizeof(int));
    for (int i = 0; i < a; i++)
    {
        alavancas[i] = baixo;
    }
    return alavancas;
}
// Função que printa a resposta dada as orientações do exercício
void print_resp(int *estado_alavancas, int melhor_improb, int a)
{
    printf("%d\n", melhor_improb);
    for (int i = 0; i < a; i++)
    {
        printf("%s%d ", (estado_alavancas[i] == cima) ? "+" : "-", i);
    }
    printf("\n");
}
// Função que verifica quanto de improbabilidade uma determinada permutação perdeu, olhando até uma determinada posição, pois as posições antes da nossa troca, nós já temos certeza
int verif_antes_improb_perdido(circuito *todos_circuitos, int *estado_alavancas, int comeco, int c, int a, int maior_perda_aceitavel) // de que não vamos alterar
{
    int improb_perdido = 0;
    for (int i = 0; i < c; i++)
    {
        circuito atual = todos_circuitos[i];
        if (atual->tamanho - 1 <= comeco + 1)
            for (int j = 0; j < a; j++)
            {
                if (maior_perda_aceitavel <= improb_perdido)
                {                    // Se a nossa improb_perdida já é maior do que o maior valor de improbabilidade que podemos
                    return INFINITO; // perder. Paramos, porque não adianta continuar a busca
                }
                if ((atual->vetor[j] == estado_alavancas[j] && j <= comeco) || (j > comeco && atual->vetor[j] != desconhecido))
                {          // Se a nossa permutação é igual a alavanca do circuito atual e está antes do começo, ou seja, esta é uma alavanca que nós já alteramos e que não iremos mais
                    break; // mexer, iremos parar, pq este circuito já estará ativado. E a segunda condição é se nós temos uma alavanca que não alteramos ainda e ela está presente
                } // no circuito, não podemos concluir nada.
                else if (j == a - 1) // Se chegamos ao final da busca e não paramos, então, este circuito não pode ser ativado.
                {
                    improb_perdido += atual->peso;
                    break;
                }
            }
    }
    return improb_perdido;
}
// Função que copia um vetor 2 em um vetor 1.
void copiar_vetor(int *v1, int *v2, int a)
{
    for (int i = 0; i < a; i++)
    {
        v1[i] = v2[i];
    }
}
// Função que utiliza backtracking para retornar qual é a maior improbabilidade de um sistema e qual é essa permutação.
void backtracing(circuito *todos_circuitos, int *estado_alavancas, int c, int a, int improb_total_sistema, int *maior_improb, int *verif, int comeco, int *melhor_sequencia)
{

    int improb_parcial_total = calcula_improbablidade(todos_circuitos, estado_alavancas, c, a), valor_perdido = 0;
    int maior_perda_aceitavel = improb_total_sistema - *maior_improb; // Variável que determina qual é o máximo de improbabilidade podemos perder, para que faça
    if (*verif)                                                       // Se já encontramos a resposta máxima possível       //sentido continuar a busca,
        return;

    if (comeco > 1) // Nós apenas olhamos quanto de improbabilidade perdemos, quando trocamos duas alavancas, pois os circuitos possuem no mínimo duas alavancas.
        valor_perdido = verif_antes_improb_perdido(todos_circuitos, estado_alavancas, comeco - 1, c, a, maior_perda_aceitavel);
    int improb_max_pos = improb_total_sistema - valor_perdido; // Variável que diz qual é o máximo de improbabilidade que uma determinada permutação pode alcançar
    if (improb_max_pos <= *maior_improb)                       // Se o máximo possível que uma permutação pode alcançar não é maior do que o valor máximo que já temos. Não faz sentido
    {                                                          // continuar a busca
        return;
    }
    if (improb_parcial_total > *maior_improb) // Se a nossa improbabilidade parcial já é maior do que a maior improbabilidade, iremos atualizar os valores
    {                                         // de maior_improb e o vetor de melhor_sequencia
        *maior_improb = improb_parcial_total;
        copiar_vetor(melhor_sequencia, estado_alavancas, a);
    }
    if (improb_parcial_total == improb_total_sistema) // Se o valor da improbabilidade parcial já for igual ao valor máximo que o sistema pode possuir, já encontramos
    {                                                 // o melhor caso possível, logo copiamos os valores de maior_improb e o vetor de melhor_sequencia e interrompemos
        *maior_improb = improb_parcial_total;         // a busca
        copiar_vetor(melhor_sequencia, estado_alavancas, a);
        *verif = 1;
        return;
    }

    for (int i = comeco; i < a; i++)
    {
        if (!*verif) // Se a busca já não encontrou o valor máximo possível, continue a procura
        {
            estado_alavancas[i] = (estado_alavancas[i] == cima) ? baixo : cima;                                                       // Inverta a alavanca
            backtracing(todos_circuitos, estado_alavancas, c, a, improb_total_sistema, maior_improb, verif, i + 1, melhor_sequencia); // Chame a recursão para alterar
                                                                                                                                      // a partir da próxima posição
            estado_alavancas[i] = (estado_alavancas[i] == cima) ? baixo : cima;                                                       // Se não valeu a pena alterar a alavanca, volte ao estado inicial
        }
        else
            return;
    }
}
// Função que encontra a melhor permutação e o melhor valor de improbabilidade
int *encontra_melhor_permutacao(circuito *todos_circuitos, int c, int a, int improb_total, int *melhor_improb)
{
    int improb_cima, improb_baixo, verif = 0;
    int *estado_alavancas_baixo = todas_alavancas_para_baixo(a);
    int *estado_alavancas_cima = todas_alavancas_para_cima(a);
    int *melhor_sequencia = malloc(a * sizeof(int));

    improb_cima = calcula_improbablidade(todos_circuitos, estado_alavancas_cima, c, a);
    improb_baixo = calcula_improbablidade(todos_circuitos, estado_alavancas_baixo, c, a);

    *melhor_improb = (improb_baixo > improb_cima) ? improb_baixo : improb_cima;
    int *melhor_estado_alavancas = (improb_baixo > improb_cima) ? estado_alavancas_baixo : estado_alavancas_cima;
    backtracing(todos_circuitos, melhor_estado_alavancas, c, a, improb_total, melhor_improb, &verif, 0, melhor_sequencia);
    free(estado_alavancas_baixo);
    free(estado_alavancas_cima);
    return melhor_sequencia;
}
// Fução que libera todos os circuitos
void libera_todos_circuitos(circuito *todos_circuitos, int c)
{
    for (int i = 0; i < c; i++)
    {
        free(todos_circuitos[i]->vetor);
        free(todos_circuitos[i]);
    }
    free(todos_circuitos);
}
