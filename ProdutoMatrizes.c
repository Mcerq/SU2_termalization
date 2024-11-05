#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoes_SU(2).h"

//Funcao que esta diretamente relacionada com o produto entre os links.

void prodMatriz (double e0, double e1, double e2, double e3, double f0, double f1, double f2,
				 double f3, double *g0, double *g1, double *g2, double *g3) {
	
	// Verificação de ponteiros nulos
        if (!g0 || !g1 || !g2 || !g3) {
                fprintf(stderr, "Erro: ponteiro de saída nulo passado para prodMatriz.\n");
                return;
        }

	*g0 = (e0 * f0) - (e1 * f1) - (e2 * f2) - (e3 * f3);
	*g1 = (e0 * f1) + (e1 * f0) - (e2 * f3) + (e3 * f2);
	*g2 = (e0 * f2) + (e1 * f3) + (e2 * f0) - (e3 * f1);
	*g3 = (e0 * f3) - (e1 * f2) + (e2 * f1) + (e3 * f0);

	
	}



void testeunitario(double a0, double a1, double a2, double a3) {

        double m = a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3;
        double Y = fabs(m - 1.0);

        if (Y > 1e-14) {
        
                printf("Erro: não unitário. Desvio de %.2e detectado.\n", Y);
        
        }

}

