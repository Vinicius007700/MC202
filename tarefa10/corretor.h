#define MAX 193 // um número primo distante de duas bases de dois
#define MAX_STRING 25
typedef struct hash *p_hash;
typedef struct no *p_no;
struct no
{
    char chave[MAX_STRING];
    p_no prox;
};
struct hash
{
    p_no vetor[MAX];
};
enum cores
{
    verde,
    amarelo,
    vermelho,
    indeterminado
};

p_hash criar_hash();
void inserir(p_hash t, char *chave);
enum cores determinar_nivel_correcao(p_hash dic, char *palavra);
void print_respostas(enum cores resposta, char *palavra);
void liberar_hash(p_hash dic);