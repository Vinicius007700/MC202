typedef struct matriz *posicoes;
typedef struct cobra *cobra;
typedef struct cabeca *cabeca;
struct cobra
{
    cobra prox;
    cobra ant;
    int linha, coluna;
};
struct cabeca
{
    cobra inicio;
    cobra rabo;
    int len_cobra;
};
cobra inicializar_corpo_cobra(int linha, int coluna);

cabeca inicializar_cabeca(cobra cobra);

cabeca movimentacao_cabeca(cabeca original, int nova_linha, int nova_coluna);

cabeca adicionar_cabeca(cabeca original, int linha, int coluna);

char **criar_matriz(int linha_incial_cobra, int col_inicial_cobra, int num_linhas, int num_colunas);

int movimentacao_tabuleiro(char comando, char **matriz, cobra corpo_cobra, cabeca cabeca,
                           int num_linhas, int num_colunas);

void print_tabuleiro(char **matriz, int num_linhas, int num_colunas);

void free_corpo_cobra(cabeca cabeca);

void free_matriz(char **matriz, int num_linhas);
