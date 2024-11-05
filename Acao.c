#include <stdio.h>	
#include <stdlib.h>
#include <math.h>
#include "funcoes_SU(2).h"



double plaqueta(int n1, int n2, int n3, int n4, int mu, int nu) {

	double a0, a1, a2, a3;
	double b0, b1, b2, b3;
	double c0, c1, c2, c3;
	int m[4];
	const int n[4] = {n1, n2, n3, n4};


	//======================================
	//Elementos da primeira matriz U(n,mu)
	//======================================
	
	a0 = U[n1][n2][n3][n4][mu][0];
	a1 = U[n1][n2][n3][n4][mu][1];
	a2 = U[n1][n2][n3][n4][mu][2];
	a3 = U[n1][n2][n3][n4][mu][3];

	//======================================
	// Coordenadas do ponto vizinho n+mu
	//======================================

    // Chama a função e recebe um novo vetor modificado
	int* resultadoMu = vizinhoPeriDir(n, mu);

	// Copia o resultado para 'm' para preservá-lo forma do escopo da função
	for(int i=0; i < COMPONENTS; i++){

		m[i] = resultadoMu[i];
	
	}

	//=======================================
	// Elementos da segunda matriz U(n+mu,nu)
	//=======================================

	b0 = U[m[0]][m[1]][m[2]][m[3]][nu][0];
	b1 = U[m[0]][m[1]][m[2]][m[3]][nu][1];
	b2 = U[m[0]][m[1]][m[2]][m[3]][nu][2];
	b3 = U[m[0]][m[1]][m[2]][m[3]][nu][3];

	//======================================================
	// Produto matricial entre U(n,mu) e U(n+mu,nu) = Unew
	//======================================================

	prodMatriz(a0, a1, a2, a3, b0, b1, b2, b3, &c0, &c1, &c2, &c3);



	
	//========================================
	// Coordenadas do ponto vizinho n+nu
	//========================================
	

	// Chama a função e recebe um novo vetor modificado
	int* resultadoNu = vizinhoPeriDir(n, nu);

	// Copia o resultado para 'm' para preservá-lo forma do escopo da função
	for(int j=0; j < COMPONENTS; j++){

		m[j] = resultadoNu[j];
	
	}
	
	vizinhoPerDir(m, nu);
	
	


	//========================================
	// Elementos da terceira matriz U(n+nu,mu)
	//========================================

	a0 = U[m[0]][m[1]][m[2]][m[3]][mu][0];
	a1 = U[m[0]][m[1]][m[2]][m[3]][mu][1];
	a2 = U[m[0]][m[1]][m[2]][m[3]][mu][2];
	a3 = U[m[0]][m[1]][m[2]][m[3]][mu][3];
	
	//=========================================================
	// Produto matricial entre Unew e U(n+nu,mu) = Unew2
	//=========================================================
	
	prodMatriz(c0, c1, c2, c3, a0, -a1, -a2, -a3, &b0, &b1, &b2, &b3);

	//========================================
	// Elementos da quarta matriz U(n,nu)
	// =======================================

	a0 = U[n1][n2][n3][n4][nu][0];
	a1 = U[n1][n2][n3][n4][nu][1];
	a2 = U[n1][n2][n3][n4][nu][2];
	a3 = U[n1][n2][n3][n4][nu][3];

	// Produto entre as matrizes U(n+j,i) e U(n,j), lembrando que temos que elas sao
	// matrizes com "dagger", no qual suas componentes espaciais ganham sinal de (-)
	// em relacao a matriz U normal.
	
	//==========================================================
	// Produto matricial entre Unew2 e U(n,nu) = Unew3
	//==========================================================

	prodMatriz(b0, b1, b2, b3, a0, -a1, -a2, -a3, &c0, &c1, &c2, &c3);

	//=========================================================
	// O Tra�o ser� a soma da diagonal da matriz Unew3.
	//=========================================================

	return c0;
}

void acao() {

	double plaq = 0.0;


	for (int n1 = 0; n1 < N; n1++) {
		for (int n2 = 0; n2 < N; n2++) {
			for (int n3 = 0; n3 < N; n3++) {
				for (int n4 = 0; n4 < NT; n4++) {
					for (int mu = 0; mu < d; mu++) {
						for (int nu = mu + 1; nu < d; nu++) {
							  
							plaq += plaqueta(n1, n2, n3, n4, mu, nu);
						  
						}
					}
				}
			}
		}
	}

	S = 0.5*beta[coupling]*(1.0-plaq / NORMALIZADOR_PLAQ );

}
