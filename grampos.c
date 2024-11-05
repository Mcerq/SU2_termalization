#include <stdio.h>
#include <stddef.h> // Para uso de size_t
#include "funcoes_SU(2).h"




void grampoSuperior(int n1, int n2, int n3, int n4, int mu, int nu, double *e0, double *e1, double *e2, double *e3) {
        int m[4];
        int p[4];
        const int n[4] = {n1, n2, n3, n4};
        int i;
        double a[COMPONENTS], b[COMPONENTS], c[COMPONENTS];

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

        prodMatriz(a[0], a[1], a[2], a[3], b[0], -b[1], -b[2], -b[3], &c[0], &c[1], &c[2], &c[3]);


        // Matriz U(n,nu):


        for (size_t i = 0; i < COMPONENTS; i++) {
        
                a[i] = U[n1][n2][n3][n4][nu][i];
        
        }

        // Produto matricial  entre U e U(n,j) :

        prodMatriz(c[0], c[1], c[2], c[3], a[0], -a[1], -a[2], -a[3], &b[0], &b[1], &b[2], &b[3]);

        *e0 = b[0];
        *e1 = b[1];
        *e2 = b[2];
        *e3 = b[3];

}


void grampoInferior(int n1, int n2, int n3, int n4, int mu, int nu, double *e0, double*e1, double *e2, double *e3) {

        int m[4];
        int p[4];
        const int n[4] = {n1, n2, n3, n4};
        double a0, a1, a2, a3;
        double b0, b1, b2, b3;
        double c0, c1, c2, c3;
        int i;

  
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

        // Para a matriz U(n+mu-nu,nu):

        a0 = U[p[0]][p[1]][p[2]][p[3]][nu][0];
        a1 = U[p[0]][p[1]][p[2]][p[3]][nu][1];
        a2 = U[p[0]][p[1]][p[2]][p[3]][nu][2];
        a3 = U[p[0]][p[1]][p[2]][p[3]][nu][3];

        //Vamos analisar o vizinho da esquerda nu (n-nu):

        // Chama a função e recebe um novo vetor modificado
	int* resultadoNu2 = vizinhoPeriEsq(n, nu);

	// Copia o resultado para 'm' para preservá-lo forma do escopo da função
	for(i = 0; i < COMPONENTS; i++){

		m[i] = resultadoNu2[i];
	
	}

        // Para a matriz U(n-nu,mu):

        b0 = U[m[0]][m[1]][m[2]][m[3]][mu][0];
        b1 = U[m[0]][m[1]][m[2]][m[3]][mu][1];
        b2 = U[m[0]][m[1]][m[2]][m[3]][mu][2];
        b3 = U[m[0]][m[1]][m[2]][m[3]][mu][3];


        // Produto matricial U = U^(+)(n+mu-nu,ni)U^(+)(n-nu,mu)

        prodMatriz(a0, -a1, -a2, -a3, b0, -b1, -b2, -b3, &c0, &c1, &c2, &c3);

	
	
	// Matriz U(n-nu,nu) O vizinho da esquerda foi reutilizado.

        a0 = U[m[0]][m[1]][m[2]][m[3]][nu][0];
        a1 = U[m[0]][m[1]][m[2]][m[3]][nu][1];
        a2 = U[m[0]][m[1]][m[2]][m[3]][nu][2];
        a3 = U[m[0]][m[1]][m[2]][m[3]][nu][3];

        // Produto matricial entre U() e U(n-nu,nu)

        prodMatriz(c0, c1, c2, c3, a0, a1, a2, a3, &b0, &b1, &b2, &b3);

        *e0 = b0;
        *e1 = b1;
        *e2 = b2;
        *e3 = b3;


}

void somaGrampos(int n1, int n2, int n3, int n4, int mu, double *b0, double *b1, double *b2, double *b3) {

        double ax0, ax1, ax2, ax3;
        double ay0, ay1, ay2, ay3;
        int nu;

        double a[COMPONENTS] = {0.0, 0.0, 0.0, 0.0};

        for (size_t nu = 0; nu < d; nu++) {
                if (mu != nu) {
                        grampoSuperior(n1, n2, n3, n4, mu, nu, &ax0, &ax1, &ax2, &ax3);


                        a[0] += ax0;
                        a[1] += ax1;
                        a[2] += ax2;
                        a[3] += ax3;

                        grampoInferior(n1, n2, n3, n4, mu, nu, &ay0, &ay1, &ay2, &ay3);

                        a[0] += ay0;
                        a[1] += ay1;
                        a[2] += ay2;
                        a[3] += ay3;

                }
        }



        *b0 = a[0];
        *b1 = a[1];
        *b2 = a[2];
        *b3 = a[3];
}


