#include <stdio.h>	
#include <stdlib.h>
#include <stddef.h> // Para uso de size_t
#include <math.h>
#include "funcoes_SU(2).h"



double plaqueta(int n1, int n2, int n3, int n4, int mu, int nu) {

	double a[COMPONENTS], b[COMPONENTS], c[COMPONENTS];
	int m[4];
	const int n[4] = {n1, n2, n3, n4};


	//======================================
	//Elementos da primeira matriz U(n,mu)
	//======================================
	
	// Atribui valores para U(n+mu, nu)
    for (size_t i = 0; i < COMPONENTS; i++) {
        
        a[i] = U[n1][n2][n3][n4][mu][i];
        
    }

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

	for (size_t i = 0; i < COMPONENTS; i++) {
        
        b[i] = U[m[0]][m[1]][m[2]][m[3]][nu][i];
        
    }

	//======================================================
	// Produto matricial entre U(n,mu) e U(n+mu,nu) = Unew
	//======================================================

	prodMatriz(a, b, c);
	
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

	for (size_t i = 0; i < COMPONENTS; i++) {
        
		
        a[i] = U[m[0]][m[1]][m[2]][m[3]][mu][i];
        
    }

	for (size_t i = 1; i < COMPONENTS; i++) {
  	
	      a[i] = -a[i]; // Torna a[i] negativa
  	  	
	
	}
	
	//=========================================================
	// Produto matricial entre Unew e U(n+nu,mu) = Unew2
	//=========================================================
	
	prodMatriz(c, a, b);

	//========================================
	// Elementos da quarta matriz U(n,nu)
	// =======================================

	for (size_t i = 0; i < COMPONENTS; i++) {
        
        a[i] = U[n1][n2][n3][n4][nu][i];
        
    }

	for (size_t i = 1; i < COMPONENTS; i++){
  	
	      a[i] = -a[i]; // Torna a[i] negativa

	
	}

	// Produto entre as matrizes U(n+j,i) e U(n,j), lembrando que temos que elas sao
	// matrizes com "dagger", no qual suas componentes espaciais ganham sinal de (-)
	// em relacao a matriz U normal.
	
	//==========================================================
	// Produto matricial entre Unew2 e U(n,nu) = Unew3
	//==========================================================

	prodMatriz(b, a, c);

	//=========================================================
	// O Tra�o ser� a soma da diagonal da matriz Unew3.
	//=========================================================

	return c[0];
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
