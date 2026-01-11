#include "centros.h"

int main()
{
    int num_cidades, conexao_cidades, populacao, dist, *vetor_dist, maior_dist_original = INFINITO, hash1, hash2;
    char cidade1[MAX_STRING], cidade2[MAX_STRING];
    scanf("%d", &num_cidades);
    p_hash info_cidades = criar_hash(num_cidades);
    for (int i = 0; i < num_cidades; i++)
    {
        scanf("%s %d", cidade1, &populacao);
        inserir_hash(info_cidades, cidade1, populacao);
    }
    p_grafo grafo = inicializa_grafo(info_cidades);
    scanf("%d", &conexao_cidades);
    for (int i = 0; i < conexao_cidades; i++)
    {
        scanf("%s %s %d", cidade1, cidade2, &dist);
        insere_aresta(grafo, hash(cidade1), hash(cidade2), dist);
    }
    distancias distancias = inicializa_distancias(info_cidades);
    for (int i = 0; i < MAX_HASH; i++)
    {
        if (info_cidades->vetor[i] != NULL)
        {
            if (grafo->adj[i] != NULL)
            {
                vetor_dist = dijkstra(grafo, i);
                inserir_distancias(distancias, vetor_dist, info_cidades, i);
                free(vetor_dist);
            }
        }
    }
    seleciona_cidades_centros_distribuicao(info_cidades, distancias, grafo, &maior_dist_original, &hash1, &hash2);
    printar_resposta(info_cidades, hash1, hash2, maior_dist_original);
    libera_tudo(grafo, info_cidades, distancias);
    return 0;
}