
// Struct que armazena os itens que fazem parte da sequência de acessos
typedef struct ordem_insercao *ordem_insercao;

typedef struct item item;

/*Struct que armazena o cache em uma fila de prioridades*/
typedef struct p_fp *p_fp;

/*Struct que armazena qual é a fila dentro de um mesmo número da sequência de acessos
Por exemplo, o servidor aparece nas posições 2,3, 10, 20. Esta struct irá armazenar essa informação*/
typedef struct fila_iguais *fila_iguais;

//Struct que aponta para o primeiro e o último elementos da sequência de acessos
typedef struct ponteiro *ponteiro; 

//Struct que armazena as principais informações de determinado servidor
typedef struct vetor_num *vetor_num;

struct fila_iguais {
    int posicoes;               
    fila_iguais prox;    
};

struct ponteiro {
    fila_iguais primeiro; 
    fila_iguais ultimo;   
};

struct vetor_num{
    int esta_no_cache;
    int pos_cache;              
    fila_iguais indice;     
    ponteiro cabeca; 
};

struct ordem_insercao{
    item *v;
    int comeco, final;

};


struct p_fp{
    int espacos_totais, espacos_ocupados;
    item *v;
};


struct item{
    int chave;
    int ordem;
};

ordem_insercao criar_lista_prioridades(int tam);
item cria_item(int entrada, int i);
p_fp cria_cache(int c);
item extrai_primeiro(ordem_insercao fprio);
void inicializa_vetor_num(int n, vetor_num  * v);
void insere(vetor_num * v, ordem_insercao fprio, int m);
void insere_cache(p_fp cache, int num, vetor_num v, int * res);
void liberar_tudo(p_fp cache, ordem_insercao fprio, vetor_num v, int n);