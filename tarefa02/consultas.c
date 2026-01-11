#include <stdio.h>
#define N_MEDICO 50
#define DOENCAS_CONHECIDAS 150
#define MAX_DOENCA 100
#define MAX_MEDICOS 30
#define MAX_CONSULTAS 100
void criar_matriz_doencas(char doencas[][DOENCAS_CONHECIDAS]){
    for (int i = 0; i < DOENCAS_CONHECIDAS; i++)
        for (int j = 0; j < DOENCAS_CONHECIDAS; j++)
            doencas[i][j] = '\0';
}
void criar_matriz_medicos(char medicos[][MAX_MEDICOS]){
    for (int i = 0; i < N_MEDICO; i++)
        for (int j = 0; j < MAX_MEDICOS; j++)
            medicos[i][j] = '\0';
}
void criar_matriz_agenda(char agenda[][MAX_CONSULTAS]){
    for (int i = 0; i < MAX_CONSULTAS; i++)
        for (int j = 0; j < MAX_CONSULTAS; j++)
            agenda[i][j] = '\0';
            
}

void add_doencas(char doencas[][DOENCAS_CONHECIDAS], int n_doencas, FILE * fp){
    /*função que adiciona as doenças a um vetor */
    char termo[DOENCAS_CONHECIDAS];
    for (int i = 0; i < n_doencas; i++){
        fgets(termo, MAX_DOENCA, fp);
        for (int j = 0; j < MAX_DOENCA; j++){
            if (termo[j] == '\n')
                break;
            doencas[i][j] = termo[j];
        
        }
    }
}
void add_medicos(char medicos[][MAX_MEDICOS], int n_medicos, FILE * fp){
    /*função que adiciona os médicos a um vetor*/
    char termo[MAX_MEDICOS];
    for (int i = 0; i < n_medicos; i++){
        fgets(termo, MAX_MEDICOS, fp);
        for (int j = 0; termo[j]!= '\n'; j++){
            medicos[i][j] = termo[j];
        }
    }
}
void registrar(char agenda[][MAX_CONSULTAS], char termo_agenda[MAX_CONSULTAS], int posicao){
    /*função responsável por registra os termos na agenda*/
    for (int i = 10; termo_agenda[i] != '\n'; i++ ){
        agenda[posicao][i-10] = termo_agenda[i];
    }
}
void voltar(char agenda[][MAX_CONSULTAS], int posicao_inicial){
    for (int j = posicao_inicial; j < MAX_CONSULTAS - 1; j++)  
        for (int i = 0; i < MAX_CONSULTAS; i++){
            agenda[j][i] = agenda[j+1][i]; 
        }

}


void remover(char agenda[][MAX_CONSULTAS], char termo_agenda[MAX_CONSULTAS]){
    /*função responsável por remover os termos da agenda*/
    int termo, posicao;
    for(int i = 0; i < MAX_CONSULTAS; i++)
        for (int j = 0; j < MAX_CONSULTAS - 8; j++){
            termo = termo_agenda[j+8];
            if (agenda[i][j] != termo_agenda[j+8]){
                if (termo == '\n'){
                    for (int l= 0; l < j; l++)
                        agenda[i][l] = '\0'; /*adiciona-se '\0' para mostrar que aquele compartimento não há nada de relevante*/
                    posicao = i;
                }else
                    break;
            }
         
        }
    voltar(agenda, posicao);/*como nós removemos um valor é necessário que voltemos todos os termos que estão acima, para que haja uma melhor realocação dos elementos, pois se nós registrarmos mais de 100 pessoas em um mesmo dia, iria ocorrer um erro*/

}  

int procura_espaços_da_agenda(char agenda[][MAX_CONSULTAS], int j, int espacos){
    /* função que dado um numero de espaços, retorna o número adicionado a 1 do espaço desejado, para retomar o número da posição do primeiro caracter depois do espaço*/
    int k = 0;
    for (int i = 0; i < MAX_DOENCA; i++){
        if (agenda[j][i] == ' ')
            k+=1;
        if (k == espacos)
            return i +1;
    }
    return 0;
    
}
int procura_primeiro_espaco_do_termo_agenda_doenca(char termo_agenda[MAX_CONSULTAS]){
    int cont = 0;
    for (int i = 0; i < MAX_DOENCA; i++){
        if (termo_agenda[i] == ' ')
            cont+=1;
        if (cont == 2)
            return i + 1;
    }
    return 0;
  
}


void alterar(char agenda[][MAX_CONSULTAS], char termo_agenda[MAX_CONSULTAS]){
    /*função responsável por alterar o diagnóstico de determinado paciente*/
    int inicio_agend, inicio_alterar;
    for (int i =0; i < MAX_CONSULTAS; i++){
        for (int j = 0; j < MAX_CONSULTAS; j++){
            if (agenda[i][j] == termo_agenda[j+8] ){
                if (agenda[i][j] == ' ' && termo_agenda[j+8] == ' '){
                    inicio_alterar = procura_espaços_da_agenda(agenda, i, 1);
                    inicio_agend = procura_primeiro_espaco_do_termo_agenda_doenca(termo_agenda);
                    for (int l = 0; l < 3; l++)
                        agenda[i][l+inicio_alterar] = termo_agenda[l + inicio_agend]; 
                    break;        
               }
            }else{
                break;
            }

    
        }
    }
}


void printar_resposta(char agenda[][MAX_CONSULTAS], int j, char medicos[][MAX_MEDICOS], char doencas[][DOENCAS_CONHECIDAS]){
    int fim, inicio, bool = 1, cont = 0;
    for (int i = 0; i < j; i++){ 
        if (agenda[i][0] != '\0'){ /* verifica se o primeiro termo da agenda é diferente de nulo para indicar que nesse compartimento há algum nome a ser printado*/
            fim = procura_espaços_da_agenda(agenda, i, 1) - 1; 
            /* variável que representa até o indice do caracter que iremos printar*/
            for (int k = 0; k < fim; k++)
                printf("%c", agenda[i][k]);/*print do nome do paciente*/
        
            printf(" atendido por ");
            inicio = procura_espaços_da_agenda(agenda, i, 2);
            for (int l = 0; l < MAX_MEDICOS; l++){
                bool = 1;
                for (int n = 0; n < 6; n ++)/* n < 6, pois o código do Médico possui apenas 6 caracteres*/
                    if (medicos[l][n] != agenda[i][n+ inicio]){/*se há um caracter difente, a preposição é falsa*/
                        bool = 0;
                        break;
                    }
                if (bool)
                    for (int m = 7; medicos[l][m]!='\0'; m++)/* m = 7, pois 7 é o índice que começa o nome do médico*/
                        printf("%c", medicos[l][m]); /*print do nome do médico*/
                    
            }
            printf(": ");
            for (int n = 0; n < DOENCAS_CONHECIDAS; n++){
                cont = 0;
                inicio = procura_espaços_da_agenda(agenda, i, 1);
                for (int l = 0; l < 3; l++){
                    if (agenda[i][inicio+l] != doencas[n][l])
                        break;

                    cont +=1; 
                
                    if (cont == 3) /* como o código do médico possui 3 letras, se o cont == 3, então, todas as letras são iguais, pois se houver alguma diferente, na linha(159) tem um break*/
                        for (int m = 4; m < MAX_DOENCA; m++){
                            if (doencas[n][m] == '\0'){ /* quando chega ao último caractere, há um break*/
                                printf("\n");
                                break;
                            }
                            printf("%c", doencas[n][m]);/*print do nome da doença*/
                    
                }
            }

        }
   
    
}

    }
}
int main(){
    int n_doencas, n_medicos, bool = 1, posicao = 0;
    char doencas[DOENCAS_CONHECIDAS][DOENCAS_CONHECIDAS], medicos[N_MEDICO][MAX_MEDICOS], agenda[MAX_CONSULTAS][MAX_CONSULTAS], termo_agenda[MAX_CONSULTAS], abrir[10];
    criar_matriz_doencas(doencas);/*funçôes(linhas 184- 186) que organizam os vetores criados*/ 
    criar_matriz_agenda(agenda);
    criar_matriz_medicos(medicos);
    FILE *fp = fopen("dados/doencas.txt", "r");
    if (fp == NULL) {
        perror("Não foi possível abrir doencas.txt");
        return 1;
    }
    fscanf(fp, "%d ", &n_doencas);
    add_doencas(doencas, n_doencas, fp);
    fclose(fp);
    FILE *f = fopen("dados/medicos.txt", "r");
    if (f == NULL){
        perror("Não foi possível abrir medicos.txt");
        return 1;
    }
    fscanf(f, "%d ", &n_medicos);
    add_medicos(medicos, n_medicos, f);
    fclose(f);
    while (bool){
        fgets(termo_agenda, MAX_CONSULTAS, stdin);
        if (termo_agenda[0] =='r'){/*se o primeiro caracter é r, temos a possibilidade de que seja registrar ou remover*/
            if (termo_agenda[2] == 'g'){
                registrar(agenda, termo_agenda, posicao);
                posicao+=1;/*a posição para adicionar o próximo termo, ao primeiro espaço vazio do veotr agenda*/
        }
            else{
                remover(agenda, termo_agenda);
                posicao-=1;
                
            }
        }else if (termo_agenda[0] == 'a'){
            if(termo_agenda[1] == 'l')
                alterar(agenda, termo_agenda);
            else
                fgets(abrir, 1, stdin);
        }
        else
                break;
    }

        printar_resposta(agenda, posicao, medicos, doencas);
        return 0;
}

