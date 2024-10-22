#include <stdio.h>
#include "funcoes_SU(2).h"
#include <stdlib.h>

void contadorLinhasBeta() {
	
	FILE *arq;
	char Linha[100];
	char *result;
	int i;
	int j;
	double temp, a, sigma;
	char filename1[100];
	
	sprintf(filename1,"//media/user/Seagate Expansion Drive/su2/arquivos_betas_NT%01d.txt", NT);
	arq = fopen(filename1, "r");
	
	if (arq == NULL){  						// Se houve erro na abertura
	
		printf("Problemas na abertura do arquivo de betas 1\n");
 			return;
	
	}
	
	i = 0;
	
	while (!feof(arq)){	// Lê uma linha (inclusive com o '\n')
 
      		result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
  			i++;
	
	}
	
	numerobeta = i;
	fclose(arq);
	
	arq = fopen(filename1, "r");
 
            if (arq == NULL){                                               // Se houve erro na abertura
 
                    printf("Problemas na abertura do arquivo de betas 2\n");
                    return;
 
            }
	
	beta = (double *) malloc(numerobeta*sizeof(double));
	
	for(j = 0; j < numerobeta; j++){
	
		fscanf(arq, "%lf, %lf, %lf, %lf\n", &temp, &beta[j], &a, &sigma);
				
	}

	fclose(arq);
}



void coldStart() {

	int n1, n2, n3, n4;
	int mu;

	for (n1 = 0; n1 < N; n1++) {
		for (n2 = 0; n2 < N; n2++) {
			for (n3 = 0; n3 < N; n3++) {
				for (n4 = 0; n4 < NT; n4++) {
					for (mu = 0; mu < d; mu++) {

						U[n1][n2][n3][n4][mu][0] = 1.0;
						U[n1][n2][n3][n4][mu][1] = 0.0;
						U[n1][n2][n3][n4][mu][2] = 0.0;
						U[n1][n2][n3][n4][mu][3] = 0.0;

					}
				}
			}
		}
	}
}

void vizinhoPeriDir() {

    	int n1;                 // Primeira entrada do vetor N.
    	int n2;                 // Segunda entrada do vetor N.
   		int n3;                 // Terceira entrada do vetor N.
    	int n4;                 // Quarta entrada do vetor NT.
    	int mu;                 // direcao que ele tem.
    	int n[4];

    	for (n1 = 0; n1 < N; n1++) {
            	for (n2 = 0; n2 < N; n2++) {
                    	for (n3 = 0; n3 < N; n3++) {
                            	for (n4 = 0; n4 < NT; n4++) {
                                    	for (mu = 0; mu < d; mu++) {

                                            	n[0] = n1;
                                            	n[1] = n2;
                                            	n[2] = n3;
                                            	n[3] = n4;
                                            	n[mu] += 1;

                                            	if (n[0] == N) {

                                                    	n[0] = 0;

                                            	}

                                            	if (n[1] == N) {

                                                    	n[1] = 0;

                                            	}
                                            	
												if (n[2] == N) {
      
	                                                	n[2] = 0;
   
                                            	}
                                            
												if (n[3] == NT) {
         
		                                            	n[3] = 0;
   
                                            	}
   
                                            	vd[n1][n2][n3][n4][mu][0] = n[0];
                                            	vd[n1][n2][n3][n4][mu][1] = n[1];
                                            	vd[n1][n2][n3][n4][mu][2] = n[2];
                                            	vd[n1][n2][n3][n4][mu][3] = n[3];
   
                                    	}
                            	}
                    	}
            	}
    	}

}

void vizinhoPeriEsq() {


    	int n1;                         // Primeira entrada do vetor N.
    	int n2;                         // Segunda entrada do vetor N.
    	int n3;                         // Terceira entrada do vetor N.
    	int n4;                         // Quarta entrada do vetor N.
    	int mu;
    	int n[4];

        for (n1 = 0; n1 < N; n1++) {
            	for (n2 = 0; n2 < N; n2++) {
    	                for (n3 = 0; n3 < N; n3++) {
                    	        for (n4 = 0; n4 < NT; n4++) {
                            	        for (mu = 0; mu < d; mu++) {

                                    	        n[0] = n1;
                                           		n[1] = n2;
                                           		n[2] = n3;
												n[3] = n4;
                                            	n[mu] -= 1;
      
	                                        	if (n[0] == -1) {
   
                                                    	n[0] = N - 1;
														  
	                                         	}

                                            	if (n[1] == -1) {

                                                    	n[1] = N - 1;

                                            	}

                                            	if (n[2] == -1) {

                                                    	n[2] = N - 1;

                                            	}

                                            	if (n[3] == -1) {

                                                    	n[3] = NT - 1;

                                            	}

                                            	ve[n1][n2][n3][n4][mu][0] = n[0];
                                            	ve[n1][n2][n3][n4][mu][1] = n[1];
                                            	ve[n1][n2][n3][n4][mu][2] = n[2];
                                            	ve[n1][n2][n3][n4][mu][3] = n[3];

                                    	}
                            	}
                    	}
            	}
    	}

}                                                

