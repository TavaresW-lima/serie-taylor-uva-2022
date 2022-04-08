#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double PI = 3.1415926535897932384626433832795;

long fatorial(int valor) {
    if(valor == 1) {
        return 1;
    } else {
        return fatorial(valor-1) * valor;
    }
}

double getRadiano(float angulo, float minutos, float segundos) {
    double radiano = angulo + (minutos/60.0) + (segundos/3600.0);
    printf("O radiano é %f", radiano);
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

int main(int argc, char const *argv[]) {
    
    double radiano = getRadiano(atof(argv[1]), atof(argv[2]), atof(argv[3]));
    double seno = getSeno(radiano, atoi(argv[4]));

    return 0;
}
