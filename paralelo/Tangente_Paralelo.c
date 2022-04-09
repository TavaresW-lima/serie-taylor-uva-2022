#include "mpi.h"
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

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    float graus = atof(argv[1]), minutos = atof(argv[2]), segundos = atof(argv[3]);
    int rank, nProcesses, i, sinal, iteracoes = atoi(argv[4]);
    double mySeno = 0, myCosseno = 0;
    double cosseno = 0, seno = 0, tangente = 0;
    double angulo;
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        angulo = getRadiano(graus, minutos, segundos);
    }

    MPI_Bcast(&iteracoes, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&angulo, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank % 2 == 0) {
        sinal = 1;
    } else {
        sinal = -1;
    }
    for(i = rank * 2; i <= iteracoes; i += pow(2,nProcesses)) {
        if(i+1 <= iteracoes)    {
            mySeno = mySeno + ( (pow(angulo, i + 1)/fatorial(i + 1)) * sinal );
        }
        myCosseno = myCosseno + ( (pow(angulo, i)/fatorial(i)) * sinal );
    }
    MPI_Reduce(&myCosseno, &cosseno, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&mySeno, &seno, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        tangente = seno/cosseno;
        printf("Resultado - %d iterações:\n", iteracoes);
        printf("Seno:\t\t\t%.20f\n", seno);
        printf("Cosseno:\t\t%.20f\n", cosseno);
        printf("Tangente:\t\t%.20f\n", tangente);
    }
    MPI_Finalize();
    return 0;
}
