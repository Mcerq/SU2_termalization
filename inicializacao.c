#include <stdio.h>
#include "funcoes_SU(2).h"
#include <stdlib.h>

void contadorLinhasBeta() {
	
	FILE *arq;
	char Linha[100];
	char *result;
	int i = 0;
	double temp, a, sigma;
	char filename1[100];
	
	sprintf(filename1,"//media/user/Seagate Expansion Drive/su2/arquivos_betas_NT%01d.txt", NT);
	arq = fopen(filename1, "r");
	
	if (arq == NULL){ // Verificação de erro
		perror("Problemas na abertura do arquivo de betas\n");
 			return;
	}
	
	// Contar o número de linhas no arquivo
	while (fgets(Linha, sizeof(Linha), arq) != NULL){ // Uso de fgets para controle de loop
 
  			i++;
	
	}
	
	numerobeta = i;
	rewind(arq); // Retornar ao início do arquivo para leitura

	// Alocação da matriz beta
	beta = (double *)alocarMatriz1D(numerobeta);
	if(beta == NULL){

		printf("Falha na alocação de memória para beta \n");
		fclose(arq); // Fechar o arquivo antes de retornar
		return;

	}

	// Ler os valores do arquivo
	for(int j = 0; j < numerobeta; j++){

		if(fscanf(arq, "%lf, %lf, %lf, %lf\n", &temp, &beta[j], &a, &sigma) != 4){ //Verificação da leitura

			print("Erro ao ler os dados do arquivo \n");
			free(beta);	 // Libera a memória alocada
			fclose(arq);	// Fechar o arquivo
			return;

		}

	}

	fclose(arq);	 // Fechar o arquivo

}



void coldStart() {

	// Verifique a integridade de U antes de usar
    if (U == NULL) {
        fprintf(stderr, "Erro: a matriz U não foi alocada corretamente.\n");
        return;
    }

	for (int n1 = 0; n1 < N; n1++) {
		for (int n2 = 0; n2 < N; n2++) {
			for (int n3 = 0; n3 < N; n3++) {
				for (int n4 = 0; n4 < NT; n4++) {
					for (int mu = 0; mu < d; mu++) {

						// Inicializa cada componente da matriz
						U[n1][n2][n3][n4][mu][0] = 1.0;
						
						 for (int comp = 1; comp < COMPONENTS; comp++) {

                            U[n1][n2][n3][n4][mu][comp] = 0.0; // Partes imaginárias

						}
					}
				}
			}
		}
	}
}




int* vizinhoPeriDir(const int vector[4], int direction){

	static int newVector[COMPONENTS];
	
	for (int i; i < COMPONENTS; i++){

		newVector[i] = vector[i];

	}

	// Incrementa a coordenada especificada por direction

 	newVector[direction] += 1;
    
	for(int i = 0; i < COMPONENTS; i++){ // Para as três primeiras dimensões

		if(i < 3 && vector[i] == N){

			newVector[i] = 0;

		}else if(i == 3 && vector[i] == NT){ // Para a quarta dimensão

			newVector[i] = 0;
		}

	}

	return newVector;

}


int* vizinhoPeriEsq(const int vector[4], int direction) {

    static int newVector[COMPONENTS];
	
	for (int i; i < COMPONENTS; i++){

		newVector[i] = vector[i];

	}

	// Incrementa a coordenada especificada por direction
    newVector[direction] -= 1;

    // Verifica a periodicidade para cada dimensão
    for (int i = 0; i < COMPONENTS; i++) {
        
		if (i < 3 && vector[i] == -1) { // Para as três primeiras dimensões
        	
			newVector[i] = N - 1;
        
		} else if (i == 3 && vector[i] == -1) { // Para a quarta dimensão
            
			newVector[i] = NT - 1;
        
		}
    
	}

	return newVector;

}