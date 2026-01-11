typedef struct grafo *p_grafo;
typedef struct no_dist *no_dist;
typedef struct no_chaves *no_chaves;
typedef struct distancia_pontos *distancia_pontos;
typedef struct fila *p_fila;
typedef struct p_no *p_no;

// estrutura que irá nos fornecer o estado da led
enum estado
{
    acesa,
    queimada,
    apagada,
};

//estrutura que irá dizer o estado de uma LED em relação a um ciclo
enum ciclo
{
    fora_ciclo,
    indeterminado,
    percorrido
};

struct p_no
{
    int dado;
    p_no prox;
};

struct fila
{
    p_no ini, fim;
};

// Estrutura que irá fornercer a chave de uma determinada distância. Por exemplo,
// dist_pontos[n].chave fornece as informações dos elementos a uma dist "n" do ponto
// que nos fornece energia
struct distancia_pontos
{
    no_chaves chave;
};
struct grafo
{
    int **adj;
    int n;
};
//Estrutura que armazena os dados de uma determinada distância em uma árvore binária
//de busca para a ordenação dos dados
struct no_chaves
{
    no_chaves esq, dir;
    enum estado estado;
    int num;
};


p_grafo criar_grafo(int n);
distancia_pontos inicializa_dist_pontos(int n);
distancia_pontos identifica_ciclos(p_grafo g, distancia_pontos original, int *dist_minima, int s, int *ciclo);
no_chaves inserir_dist_pontos(no_chaves original, int num);
p_fila criar_fila();
void insere_conexao(p_grafo grafo, int conex_1, int conex_2, int s);
void determinar_distancias_da_raiz(p_grafo g, int s, int *dist_minima);
void inserir_led_apagada(p_grafo g, int ponto1, int ponto2, distancia_pontos distancia_pontos, int *ciclo, int *dist_minima);
void printar_leds_ordenadas_distancia_pontos(distancia_pontos dist_pontos, int n);
void operacoes_para_apagar_led(p_grafo g, int s, int *dist_minima, distancia_pontos distancia_pontos);
void liberar_tudo(p_grafo g, int *ciclo, int *dist_minima, distancia_pontos dist_pontos);
void destruir_fila(p_fila f);
void enfileira(p_fila f, int x);
void troca_para_led_apagada(no_chaves original, int num);
int desenfileira(p_fila f);
int fila_vazia(p_fila f);
int *inicializa_ciclos(p_grafo g);