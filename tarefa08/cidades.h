#define num_coordenadas 4
#define tamanho_max_nome 10
typedef struct arvore *arvore;

struct arvore
{
    int pos_x;
    int pos_y;
    char nome[tamanho_max_nome];
    double centro_x;
    double centro_y;
    arvore filhos[num_coordenadas];
};
enum coordenadas
{
    NO,
    NE,
    SO,
    SE
};
int encontrar_coordenadas(arvore original, int pos_x, int pos_y);
arvore inicializa_arvore(int tamanho);
arvore cria_novo_interno(arvore original, enum coordenadas coord);
arvore inserir_cidade(enum coordenadas coord, arvore original, int pos_x, int pos_y, char *nome);
arvore inserir_elemento(arvore original, int pos_x, int pos_y, char *nome);
arvore remocao(arvore original, int pos_x, int pos_y, char nome[tamanho_max_nome]);
int busca_por_ponto(arvore original, int pos_x, int pos_y, char *nome);
void busca_por_regiao(arvore original, int pos_x, int pos_y, int dist, char ** vetor_saida, int * num_elementos_vetor);
void liberar_arvore(arvore original);
void printar_cidades_do_vetor(char ** vetor_saida, int num_elementos_vetor, int dist, int pos_x, int pos_y);
void liberar_vetor(char ** vetor_saida, int num_elementos_vetor);
