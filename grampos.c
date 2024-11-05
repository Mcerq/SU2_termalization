#include <stdio.h>
#include <stddef.h> // Para uso de size_t
#include <string.h>
#include "funcoes_SU(2).h"




void grampoSuperior(int n1, int n2, int n3, int n4, int mu, int nu, double e[COMPONENTS]) {
        int m[4];
        int p[4];
        const int n[4] = {n1, n2, n3, n4};
        int i;
        double a[COMPONENTS], b[COMPONENTS], c[COMPONENTS];

        // Inicializa todos os arrays com zero
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));



        //Vamos analisar o vizinho da direita mu (n+mu):


        // Chama a função e recebe um novo vetor modificado
	int* resultadoMu = vizinhoPeriDir(n, mu);

	// Copia o resultado para 'm' para preservá-lo forma do escopo da função
	for(i=0; i < COMPONENTS; i++){

		m[i] = resultadoMu[i];
	
	}

        // Atribui valores para U(n+mu, nu)
        for (size_t i = 0; i < COMPONENTS; i++) {
        
                a[i] = U[m[0]][m[1]][m[2]][m[3]][nu][i];
        
        }
        
        // Chama a função e recebe um novo vetor modificado
	int* resultadoNu = vizinhoPeriDir(n, nu);

	// Copia o resultado para 'm' para preservá-lo forma do escopo da função
	for(i=0; i < COMPONENTS; i++){

		p[i] = resultadoNu[i];
	
	}
        
         // Atribui valores para U(n+nu, mu)
        for (size_t i = 0; i < COMPONENTS; i++) {
                
                b[i] = U[p[0]][p[1]][p[2]][p[3]][mu][i];
        
        }

	        // Produto matricial U = U(n+mu,nu)U^(+)(n+nu,mu):
        
        for (size_t i = 1; i < COMPONENTS; i++) {
    	
	      b[i] = -b[i]; // Torna b[i] negativa
	
	}

        prodMatriz(a, b, c);


        // Matriz U(n,nu):


        for (size_t i = 0; i < COMPONENTS; i++) {
        
                a[i] = U[n1][n2][n3][n4][nu][i];
        
        }

        // Produto matricial  entre U e U(n,j) :

        for (size_t i = 1; i < COMPONENTS; i++) {
    	
	      a[i] = -a[i]; // Torna b[i] negativa
	
	}

        prodMatriz(c, a, b);

       // Copia os resultados de b para e
        for (size_t i = 0; i < COMPONENTS; i++) {
               
                e[i] = b[i];
        
        }

}


void grampoInferior(int n1, int n2, int n3, int n4, int mu, int nu, double e[COMPONENTS]) {

        int m[4];
        int p[4];
        const int n[4] = {n1, n2, n3, n4};
        double a[COMPONENTS];
        double b[COMPONENTS];
        double c[COMPONENTS];
        int i;

        // Inicializa todos os arrays com zero
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
  
	//Vamos analisar o vizinho da esquerda nu (n-nu):

        // Chama a função e recebe um novo vetor modificado
	int* resultadoNu = vizinhoPeriEsq(n, nu);

	// Copia o resultado para 'm' para preservá-lo forma do escopo da função
	for(i = 0; i < COMPONENTS; i++){

		m[i] = resultadoNu[i];
	
	}

        // Vamos analisar o vizinho da direira n+mu-nu:

         // Chama a função e recebe um novo vetor modificado
	int* resultadoNuMu = vizinhoPeriDir(m, mu);

	// Copia o resultado para 'm' para preservá-lo forma do escopo da função
	for(i = 0; i < COMPONENTS; i++){

		p[i] = resultadoNuMu[i];
	
	}

        // Atribui valores para a matriz U(n+mu-nu, nu)
        for (size_t j = 0; j < COMPONENTS; j++) {
                
                a[j] = U[p[0]][p[1]][p[2]][p[3]][nu][j];
        
        }

        for (size_t j = 1; j < COMPONENTS; j++){
  	
	      a[j] = -a[j]; // Torna a[i] negativa

	
	}

        //Vamos analisar o vizinho da esquerda nu (n-nu):

        // Chama a função e recebe um novo vetor modificado
	int* resultadoNu2 = vizinhoPeriEsq(n, nu);

	// Copia o resultado para 'm' para preservá-lo forma do escopo da função
	for(i = 0; i < COMPONENTS; i++){

		m[i] = resultadoNu2[i];
	
	}

        // Para a matriz U(n-nu,mu):

        for (size_t j = 0; j < COMPONENTS; j++) {
                
                b[j] = U[m[0]][m[1]][m[2]][m[3]][mu][j];
        
        }

        for (size_t j = 1; j < COMPONENTS; j++){
  	
	      b[j] = -b[j]; // Torna a[i] negativa

	
	}


        // Produto matricial U = U^(+)(n+mu-nu,ni)U^(+)(n-nu,mu)

        prodMatriz(a, b, c);

	
	
	// Matriz U(n-nu,nu) O vizinho da esquerda foi reutilizado.
        for (size_t i = 0; i < COMPONENTS; i++) {
        
                a[i] = U[m[0]][m[1]][m[2]][m[3]][nu][i];
        
        }

        // Produto matricial entre U() e U(n-nu,nu)

        prodMatriz(c, a, b);

        // Copia os resultados de b para e
        for (size_t j = 0; j < COMPONENTS; j++) {
                
                e[j] = b[j];
        
        }


}

void somaGrampos(int n1, int n2, int n3, int n4, int mu, double b[COMPONENTS]) {

        double ax[COMPONENTS];
        double ay[COMPONENTS];
        int nu;

        double a[COMPONENTS] = {0.0, 0.0, 0.0, 0.0};

        for (size_t nu = 0; nu < d; nu++) {
                if (mu != nu) {
                        grampoSuperior(n1, n2, n3, n4, mu, nu, ax);


                        a[0] += ax[0];
                        a[1] += ax[1];
                        a[2] += ax[2];
                        a[3] += ax[3];

                        grampoInferior(n1, n2, n3, n4, mu, nu, ay);

                        a[0] += ay[0];
                        a[1] += ay[1];
                        a[2] += ay[2];
                        a[3] += ay[3];

                }
        }

        // Copia os resultados de b para e
        for (size_t i = 0; i < COMPONENTS; i++) {
        
                b[i] = a[i];
        
        }

}


