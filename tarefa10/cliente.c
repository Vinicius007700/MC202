#include <stdio.h>
#include "corretor.h"
int main()
{
    int m, n;
    p_hash dicionario = criar_hash();
    char palavra[MAX_STRING];
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        scanf("%s", palavra);
        inserir(dicionario, palavra);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%s", palavra);
        enum cores resposta = determinar_nivel_correcao(dicionario, palavra);
        print_respostas(resposta, palavra);
    }
    liberar_hash(dicionario);
    return 0;
}