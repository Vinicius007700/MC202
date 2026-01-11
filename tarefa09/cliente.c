#include <stdio.h>
#include "cache.h"
int main(){
    p_fp cache;
    int len_cache, n, m,
    //Variável responsável pela contagem de trocas. 
    res = 0;
    ordem_insercao fprio;
    vetor_num v;
    scanf("%d %d %d", &len_cache, &n, &m);
    fprio = criar_lista_prioridades(m);
    inicializa_vetor_num(n, &v);
    insere(&v, fprio, m);
    cache = cria_cache(len_cache);
 
    for (int i = 0; i < m; i++){
        item utilizado = extrai_primeiro(fprio);
        insere_cache(cache, utilizado.chave, v, &res);
    }
    printf("%d\n", res);
    liberar_tudo(cache, fprio, v, n);

    return 0;
    
}


