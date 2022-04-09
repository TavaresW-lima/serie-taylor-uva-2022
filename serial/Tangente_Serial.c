#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const double PI = 3.1415926535897932384626433832795;

long fatorial(int valor) {
    if(valor == 1 || valor == 0) {
        return 1;
    } else {
        return fatorial(valor-1) * valor;
    }
}

double getRadiano(float angulo, float minutos, float segundos) {
    double radiano = angulo + (minutos/60.0) + (segundos/3600.0);
    return radiano * (PI/180.0);
}

double getSeno(double angulo, int iteracoes) {
    int i, sinal = 1;
    double seno = 0;
    for(i = 1; i <= iteracoes; i += 2) {
        seno = seno + ( (pow(angulo, i)/fatorial(i)) * sinal );
        sinal = sinal * -1;
    }
    return seno;
}

double getCosseno(double angulo, int iteracoes) {
    int i, sinal = 1;
    double cosseno = 0;
    for(i = 0; i <= iteracoes; i += 2) {
        cosseno = cosseno + ( (pow(angulo, i)/fatorial(i)) * sinal );
        sinal = sinal * -1;
    }
    return cosseno;
}

double getTangente(double seno, double cosseno) {
    double tangente =  0;
    return tangente = seno/cosseno;
}

int main(int argc, char const *argv[]) {
    float graus = atof(argv[1]), minutos = atof(argv[2]), segundos = atof(argv[3]);
    int iteracoes = atoi(argv[4]);

    clock_t inicio = clock();
    
    double radiano = getRadiano(graus, minutos, segundos);
    double seno = getSeno(radiano, iteracoes);
    double cosseno = getCosseno(radiano, iteracoes);
    double tangente = getTangente(seno, cosseno);

    clock_t fim = clock();
    double tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Resultados - %d Iterações ---------\n", iteracoes);
    printf("Seno:\t\t\t%.20f\n", seno);
    printf("Cosseno:\t\t%.20f\n", cosseno);
    printf("Tangente:\t\t%.20f\n", tangente);
	printf("Tempo Decorrido:\t%.8f segundos", tempo_decorrido);

    return 0;
}
