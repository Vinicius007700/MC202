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
circuito *cria_vetor_com_todos_circuitos(int c, int a, int *peso_total);
int * encontra_melhor_permutacao(circuito *todos_circuitos, int c, int a, int improb_total, int * melhor_improb);
void print_resp(int *estado_alavancas, int melhor_improb, int a);
void libera_todos_circuitos(circuito *todos_circuitos, int c);
