#include <stdio.h>
#include <math.h>
#include "funcoes_SU(2).h"
#include <stdlib.h>		


void banhoTermico(int n1, int n2, int n3, int n4, int mu, 
	  	  		  double f[COMPONENTS], 
                  double e[COMPONENTS]) {

	double V[COMPONENTS];
	double r1, r2, r3;
	double ax[COMPONENTS];
	double aux21, aux_escalar;
	double lambda2;
	double x[COMPONENTS];
	double aux[COMPONENTS];
	double a;


	// Vamos agora gerar a matriz V a partir dos grampos:
	somaGrampos (n1, n2, n3, n4, mu, ax);

	a = sqrt(ax[0] * ax[0] + ax[1] * ax[1] + ax[2] * ax[2] + ax[3] * ax[3]);
	V[0] = ax[0]/a;
	V[1] = ax[1]/a;
	V[2] = ax[2]/a;
	V[3] = ax[3]/a;
	
	f[0] = ax[0];
	f[1] = ax[1];
	f[2] = ax[2];
	f[3] = ax[3];

	//Gerando os novos valores para o link:
	aux21 = 2.0;
	lambda2 = 0.0;

	while (aux21 > 1.0-lambda2) {
		
		r1 = ranmar();
		r2 = ranmar();
		r3 = ranmar();
		
		aux_escalar = cos(2.0 *  pi * r2);
		lambda2 = -(log(r1) + aux_escalar*aux_escalar*log(r3)) / (2.0*a*beta[coupling]);
		
		aux_escalar = ranmar();
		aux21 = pow(aux_escalar,2);
	}

	x[0] = 1.0 - 2.0 * lambda2;
	aux21 = 2.0;

	while (aux21 > 1.0) {
	
		r1 = aleatorio();
		r2 = aleatorio();
		r3 = aleatorio();
		aux21 = r1 * r1 + r2 * r2 + r3 * r3;
	
	}
	
	aux_escalar = sqrt((1.0 - pow(x[0],2)) / aux21);
	x[1] = aux_escalar * r1;
	x[2] = aux_escalar * r2;
	x[3] = aux_escalar * r3;
	
	for (size_t j = 1; j < COMPONENTS; j++){
  	
	      V[j] = -V[j]; // Torna a[i] negativa

	
	}

	// Vamos aqui colocar o novo valor para o link
	prodMatriz(x, V, aux);
	
	e[0] = aux[0];
	e[1] = aux[1];
	e[2] = aux[2];
	e[3] = aux[3];

}

double novaacaoHeatBath(int n1, int n2, int n3, int n4, int mu) {
	
	double heat_bath_scalar;
	double u0, u1, u2, u3;
	double ax[COMPONENTS];
	double aux[COMPONENTS];
	
	// Em primeiro lugar vamos guardar os valores do link para o calculo de 'dS'
	u0 = U[n1][n2][n3][n4][mu][0];
	u1 = U[n1][n2][n3][n4][mu][1];
	u2 = U[n1][n2][n3][n4][mu][2];
	u3 = U[n1][n2][n3][n4][mu][3];
	
	// Teste para saber se os links realmente sao unitarios.
	testeunitario(u0, u1, u2, u3);
	
	// Utilizacao do algoritmo de Banho Termico.
	banhoTermico(n1, n2, n3, n4, mu, ax, aux);
	
	// Novos links adicionados abaixo.
	U[n1][n2][n3][n4][mu][0] = aux[0];
	U[n1][n2][n3][n4][mu][1] = aux[1];
	U[n1][n2][n3][n4][mu][2] = aux[2];
	U[n1][n2][n3][n4][mu][3] = aux[3];
	
	// Novo teste para unitariedade de links.
	testeunitario(aux[0], aux[1], aux[2], aux[3]);
	
	// =============================================
	// Calculo para a nova acao de gauge.		
	// =============================================
            heat_bath_scalar = 0.5*beta[coupling]*(ax[0] * (u0 - aux[0]) -
                    ax[1] * (u1 - aux[1]) -
                    ax[2] * (u2 - aux[2]) -
                    ax[3] * (u3 - aux[3]))/(NORMALIZADOR_PLAQ);
	
	
	return heat_bath_scalar;
}

void heatSweep() {
	
	int n1, n2, n3, n4;
	int mu;
	
	for (n1 = 0; n1 < N; n1++) {
		for (n2 = 0; n2 < N; n2++) {
			for (n3 = 0; n3 < N; n3++) {
				for (n4 = 0; n4 < NT; n4++) {
					for (mu = 0; mu < d; mu++) {
						S += novaacaoHeatBath(n1, n2, n3, n4, mu);
					}
				}
			}
		}
	}
}

void termalizacaoHeatBath() {
	int i, varred;
	double plaquet;
	
	// Caso seja necessario o calculo de plaquetas para termalizacao.
	FILE *func;
	char filename[200];
	sprintf(filename, "plaq_N%01d_NT%01d_beta%0.4f.txt", N, NT, beta[coupling]);
   		 	
	func = fopen(filename, "w+");
		
	plaquet = 1- 2*S/beta[coupling];
		
	fprintf(func, "%d,%.12f\n", 0, plaquet);
	
	if(observavel == 1){
		
		varred = 1000;
	
	}else if(observavel == 2){
		
		varred = 600; // Para 72^3 8, para os outros e 1500.
	
	}
	
	for (i = 0; i < varred; i++) {
		
		heatSweep();
		
			plaquet = 1- 2*S/beta[coupling];
			fprintf(func,"%d,%.12f\n", i+1, plaquet);
		
		printf("Falta %.2f  por cento para termalizar\n", (float) (i*100)/varred);
	
	}
	
	fclose(func);
}