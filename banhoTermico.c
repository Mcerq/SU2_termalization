#include <stdio.h>
#include <math.h>
#include "funcoes_SU(2).h"
#include <stdlib.h>		


void banhoTermico(int n1, int n2, int n3, int n4, int mu, 
	  	  		  double *f0, double *f1, double *f2, double *f3, 
                  double *e0, double *e1, double *e2, double *e3) {

	double V0, V1, V2, V3;
	double r1, r2, r3;
	double ax0, ax1, ax2, ax3;
	double aux21, aux;
	double lambda2;
	double x0, x1, x2, x3;
	double aux0, aux1, aux2, aux3;
	double a;


	// Vamos agora gerar a matriz V a partir dos grampos:
	somaGrampos (n1, n2, n3, n4, mu, &ax0, &ax1, &ax2, &ax3);

	a = sqrt(ax0*ax0 + ax1 * ax1 + ax2 * ax2 + ax3 * ax3);
	V0 = ax0/a;
	V1 = ax1/a;
	V2 = ax2/a;
	V3 = ax3/a;
	
	*f0 = ax0;
	*f1 = ax1;
	*f2 = ax2;
	*f3 = ax3;

	//Gerando os novos valores para o link:
	aux21 = 2.0;
	lambda2 = 0.0;

	while (aux21 > 1.0-lambda2) {
		
		r1 = ranmar();
		r2 = ranmar();
		r3 = ranmar();
		
		aux = cos(2.0*pi*r2);
		lambda2 = -(log(r1) + aux*aux*log(r3)) / (2.0*a*beta[coupling]);
		
		aux = ranmar();
		aux21 = pow(aux,2);
	}

	x0 = 1.0 - 2.0 * lambda2;
	aux21 = 2.0;

	while (aux21 > 1.0) {
	
		r1 = aleatorio();
		r2 = aleatorio();
		r3 = aleatorio();
		aux21 = r1 * r1 + r2 * r2 + r3 * r3;
	
	}
	
	aux = sqrt((1.0 - pow(x0,2)) / aux21);
	x1 = aux * r1;
	x2 = aux * r2;
	x3 = aux * r3;
	
	// Vamos aqui colocar o novo valor para o link
	prodMatriz(x0, x1, x2, x3, V0, -V1, -V2, -V3, &aux0, &aux1, &aux2, &aux3);
	
	*e0 = aux0;
	*e1 = aux1;
	*e2 = aux2;
	*e3 = aux3;

}

double novaacaoHeatBath(int n1, int n2, int n3, int n4, int mu) {
	
	double aux;
	double u0, u1, u2, u3;
	double ax0, ax1, ax2, ax3;
	double aux0, aux1, aux2, aux3;
	
	// Em primeiro lugar vamos guardar os valores do link para o calculo de 'dS'
	u0 = U[n1][n2][n3][n4][mu][0];
	u1 = U[n1][n2][n3][n4][mu][1];
	u2 = U[n1][n2][n3][n4][mu][2];
	u3 = U[n1][n2][n3][n4][mu][3];
	
	// Teste para saber se os links realmente sao unitarios.
	testeunitario(u0, u1, u2, u3);
	
	// Utilizacao do algoritmo de Banho Termico.
	banhoTermico(n1, n2, n3, n4, mu, &ax0, &ax1, &ax2, &ax3, &aux0, &aux1, &aux2, &aux3);
	
	// Novos links adicionados abaixo.
	U[n1][n2][n3][n4][mu][0] = aux0;
	U[n1][n2][n3][n4][mu][1] = aux1;
	U[n1][n2][n3][n4][mu][2] = aux2;
	U[n1][n2][n3][n4][mu][3] = aux3;
	
	// Novo teste para unitariedade de links.
	testeunitario(aux0, aux1, aux2, aux3);
	
	// =============================================
	// Calculo para a nova acao de gauge.		
	// =============================================
            aux = 0.5*beta[coupling]*(ax0 * (u0 - aux0) -
                    ax1 * (u1 - aux1) -
                    ax2 * (u2 - aux2) -
                    ax3 * (u3 - aux3))/(NR*NR*NR*NTR*6.0);
	
	
	return aux;
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