#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

#define FILHO_ESQ(i) (2*i + 1)
#define FILHO_DIR(i) (2*i + 2)
#define PAI(i) ((i-1)/2)
#define FORA_FILA 10000000
#define SIM 1
#define NAO 0


// função que troca dois elementos definidos pela struct item
void troca_itens(item *a, item *b) {
    item temp = *a;
    *a = *b;
    *b = temp;
}

// Função que retorna a prioridade do próximo elemento, em relação do primeiro.
int busca_prioridade_prox_elemento(vetor_num v, int chave){
    if(v[chave].cabeca->primeiro->prox != NULL)
        return v[chave].cabeca->primeiro->prox->posicoes;
    return FORA_FILA;

}
 ordem_insercao criar_lista_prioridades(int tam){
    ordem_insercao fprio = malloc(sizeof(struct ordem_insercao));
    fprio->v = malloc(tam * sizeof(struct item));
    fprio->comeco = 0;
    fprio->final = 0;
    return fprio;
 }   


item cria_item(int entrada, int i){
    item item = {entrada, i};
    return item;
}

p_fp cria_cache(int c){
    p_fp c_cache = malloc(sizeof(struct p_fp));
    c_cache->v = malloc(c * sizeof(struct item));
    c_cache->espacos_totais = c;
    c_cache->espacos_ocupados = 0;
    return c_cache;
}

//Função que remove o primeiro elemento dos próximos elementos no vetor_num, pois temos que atualizar a informação de que 
//este elemento já foi colocado dentro do cache
void remove_primeiro(vetor_num v,int chave, int esta_no_cache){
    //Variável que aponta para o primeiro elemento
    fila_iguais aux;
    aux = v[chave].cabeca->primeiro;
    if (aux == NULL){
        v[chave].cabeca->ultimo = NULL;
    }
    if (esta_no_cache)
        v[chave].esta_no_cache = SIM;
    else{
        v[chave].esta_no_cache = NAO;
    }    
    v[chave].cabeca->primeiro = aux->prox; // o primeiro elemento irá apontar agora para o próximo
    free(aux);
}

// Função que verifica se determinado elemento está no cache
int verifica_se_esta_no_cache(vetor_num v, int chave){
    return v[chave].esta_no_cache;
}
// Função que atualiza as posições de determinado elemento no cache, pois ao fazer trocas, ela mudará também
void troca_posicoes_do_cache_no_vetor(int chave1, int chave2, vetor_num v){
    int pos1_antiga = v[chave1].pos_cache;
    v[chave1].pos_cache = v[chave2].pos_cache;
    v[chave2].pos_cache = pos1_antiga;
}
void desce_no_heap(p_fp cache, vetor_num v, int k) {
    int maior_filho, chave1, chave2;
    
    while (FILHO_ESQ(k) < cache->espacos_ocupados) {
        maior_filho = FILHO_ESQ(k);

        if (FILHO_DIR(k) < cache->espacos_ocupados &&
            cache->v[FILHO_DIR(k)].ordem > cache->v[maior_filho].ordem) {
            maior_filho = FILHO_DIR(k);
        }
    if (cache->v[k].ordem < cache->v[maior_filho].ordem) {
        troca_itens(&cache->v[k], &cache->v[maior_filho]);
        chave1 = cache->v[k].chave;
        chave2 = cache->v[maior_filho].chave;
        troca_posicoes_do_cache_no_vetor(chave1, chave2, v);
        k = maior_filho;
    }
    else
        break;
}
}

void sobe_no_heap(p_fp cache, vetor_num v, int k) {
    int chave1, chave2; 
    while (k > 0 && cache->v[PAI(k)].ordem < cache->v[k].ordem) {
        troca_itens(&cache->v[k], &cache->v[PAI(k)]);
        chave1 = cache->v[k].chave;
        chave2 = cache->v[PAI(k)].chave; 
        troca_posicoes_do_cache_no_vetor(chave1,chave2, v);
        k = PAI(k);
    }
}

//Função que insere um item no cache antes dele encher na última posição, sem precisar fazer nenhuma substituição
void insere_no_cache_antes_de_encher(p_fp cache, vetor_num v, item item){
    cache->v[cache->espacos_ocupados] = item;
    v[item.chave].pos_cache = cache->espacos_ocupados;
    cache->espacos_ocupados++;
    sobe_no_heap(cache, v, cache->espacos_ocupados - 1); // Para manter a fila de prioridades correta
}
 // Função que atualiza o cache, atualizando quem é o próximo elemento.
void atualiza_cache_para_repetidos(p_fp cache, vetor_num v, int num){
    item item = {num , busca_prioridade_prox_elemento(v, num)};
    cache->v[v[num].pos_cache] = item; // Colocamos na posição do servidor antigo do cache a posição do próximo servidor
    sobe_no_heap(cache, v, v[num].pos_cache);

}
// Função que atualiza a informação de quem está no cache, no vetor_num
void atualiza_quem_esta_cache(vetor_num v, int chave ){
    v[chave].esta_no_cache = NAO;
}

// Função que é responsável por inserir no cache os novos elementos
void insere_cache(p_fp cache, int num, vetor_num v, int * res){
    if(verifica_se_esta_no_cache(v, num)){ // Se determinado elemento já está no cache
        atualiza_cache_para_repetidos(cache, v, num);
        remove_primeiro(v, num, SIM);
        return;

    }
    item item = {num, busca_prioridade_prox_elemento(v, num)};
    if(cache->espacos_totais > cache->espacos_ocupados){ // Se há espaço para adicionar elementos no cache, sem precisar repetir
            insere_no_cache_antes_de_encher(cache, v, item);
            remove_primeiro(v, num, SIM);
            (*res)++; // Como houve trocas, podemos atualizar a variável res
            return;

    }
    remove_primeiro(v, num, SIM);
    atualiza_quem_esta_cache(v, cache->v[0].chave);
    cache->v[0] = item; // Colocamos na posição 0 do cache, o novo elemento, pois sempre removemos o elemento mais distante que sempre estará nesta posição
    v[item.chave].pos_cache = 0;  // atualizamos que o novo elemento está na posição 0 do cache
    desce_no_heap(cache, v, 0);
    (* res) ++; // Como houve trocas, podemos atualizar a variável res
} 

//Função que adiciona os itens no vetor_num
void add_item_vetor(item item, vetor_num  *v){
    if ((*v)[item.chave].cabeca == NULL) { // se o elemento não foi adicionado ainda, temos que alocar a memória primeiro
        (*v)[item.chave].cabeca = malloc(sizeof(struct ponteiro));
        (*v)[item.chave].cabeca->primeiro = NULL;
        (*v)[item.chave].cabeca->ultimo = NULL;  
        (*v)[item.chave].indice = NULL;   
        (*v)[item.chave].pos_cache = 0;
    }

    // Cria um novo nó para a fila
    fila_iguais novo = malloc(sizeof(struct fila_iguais));
    novo->posicoes = item.ordem; // Define a posição
    novo->prox = NULL; 

    // Se não há elementos na fila, inicializa o primeiro e o último
    if ((*v)[item.chave].cabeca->primeiro == NULL) {
        (*v)[item.chave].cabeca->primeiro = novo; // O primeiro é o novo nó
        (*v)[item.chave].cabeca->ultimo = novo;   
    } else {
        // Se já existem elementos, adiciona ao final
        (*v)[item.chave].cabeca->ultimo->prox = novo; // Conecta o último ao novo
        (*v)[item.chave].cabeca->ultimo = novo; // Atualiza o último
    }

}
//Função que insere a entrada, nas estruturas de dados
void insere(vetor_num * v, ordem_insercao fprio, int m){
    int num;
    for(int i = 0; i < m; i++){
        scanf("%d", &num);
        item item = {num, i};
        add_item_vetor(item, v);
        fprio->v[fprio->final++] = item;
    }
}



void inicializa_vetor_num(int n, vetor_num  * v){
    * v = malloc(n * sizeof(struct vetor_num));
    for(int i = 0; i< n; i++){
        (* v)[i].cabeca = malloc(sizeof(struct ponteiro));
        (* v)[i].cabeca->primeiro = (* v)[i].cabeca->ultimo = (* v)[i].indice = NULL;
        (* v)[i].esta_no_cache = NAO;
    }
}



//Função que extrai o primeiro elemento da fprio
item extrai_primeiro(ordem_insercao fprio){
    item min_item = fprio->v[fprio->comeco++];
    return min_item;
}
// Função que libera a memória
void liberar_tudo(p_fp cache, ordem_insercao fprio, vetor_num v, int n){
    for (int i = 0; i < n; i++ ){
        free(v[i].cabeca);
    }
    free(v);
    free(fprio->v);
    free(fprio);
    free(cache->v);
    free(cache);
}
