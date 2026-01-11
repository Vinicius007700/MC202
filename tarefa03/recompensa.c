#include <stdio.h>
#define MAX 36


double probabilidade(int rodadas, int distancia){ //função recursiva que calcula o número de probabilidades
    double prob = 0;
    if (rodadas > 0){
        for (int dado=1; dado < 7; dado++){
            if (dado < distancia)
                prob += (1.0/6)*probabilidade(rodadas- 1, distancia - dado);
            else if (dado == distancia)
                prob += 1.0/6;
        }
    }
    return prob;

}
int main(){
    int n, x;
    scanf("%d %d", &n, &x);
    printf("%.3lf\n", probabilidade(n, x));
    return 0;
}