#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoes_SU(2).h"

//Funcao que esta diretamente relacionada com o produto entre os links.

void prodMatriz (double e[COMPONENTS], double f[COMPONENTS], double g[COMPONENTS]) {
	
	
	g[0] = (e[0] * f[0]) - (e[1] * f[1]) - (e[2] * f[2]) - (e[3] * f[3]);
	g[1] = (e[0] * f[1]) + (e[1] * f[0]) - (e[2] * f[3]) + (e[3] * f[2]);
	g[2] = (e[0] * f[2]) + (e[1] * f[3]) + (e[2] * f[0]) - (e[3] * f[1]);
	g[3] = (e[0] * f[3]) - (e[1] * f[2]) + (e[2] * f[1]) + (e[3] * f[0]);

	
	}



void testeunitario(double a0, double a1, double a2, double a3) {

        double m = a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3;
        double Y = fabs(m - 1.0);

        if (Y > 1e-14) {
        
                printf("Erro: não unitário. Desvio de %.2e detectado.\n", Y);
        
        }

}

