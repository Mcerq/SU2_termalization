#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include "funcoes_SU(2).h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	clock_t Total[2];
	Total[0] = clock();
	
	int i, j, k, F;
	double tabela, novobeta;
	printf("\n\n\n\n");
	printf("==============================\n");
	printf("PROGRAMA QUE FAZ TERMALIZACAO\n");
	printf("==============================\n\n\n");
	
		
	printf("   Para o calculo de rede a temperatura zero, digite 1. Para o calculo de rede a temperatura finita, digite 2: ");
	scanf("%d", &temperatura);
	printf("\n\n\n");
	printf("   Agora, vamos gerar configuracoes termalizadas com diferentes objetivos.\n");
	printf("   Para observaveis (plaqueta, polyakov...), digite 1. Para a fixacao de gauge, digite 2: ");
	scanf("%d", &observavel);
	
	
	contadorLinhasBeta();	
	
	printf("\n\n");
	for(coupling = 0; coupling < numerobeta-1; coupling++){  
	
		printf("Calculo para beta = %.7f\n\n", beta[coupling]);

		//===============================================================================================================
		// Iniciando o gerador de numeros aleatorios 
		//===============================================================================================================
	
	
		srand(time(NULL)); 						// Inicia semente do gerador pseudo-aleatorio;  
		rmarin((int)rand() % 31328, (int)rand() % 30081); 		// inicia a funcao Ranmar;

		//===============================================================================================================
		// Funcoes de inicializacao do  programa
		//===============================================================================================================
		
		U = (double ******)alocarMatriz6D(N, N, N, NT, d, 4);
	//	vd = (int ******)alocarMatriz6D(N, N, N, NT, d, 4);
	//	ve = (int ******)alocarMatriz6D(N, N, N, NT, d, 4);
		//U = alocarMatrizReal (N, N, N, NT, d, 4);
		//vd = alocarMatrizInteiro (N, N, N, NT, d, 4);
		//ve = alocarMatrizInteiro (N, N, N, NT, d, 4);
		coldStart();              		// Faz a inicializacao das matrizes de links como matriz unitaria;
	

		//=============================================================================================
		// Termalizacao do programa
		//=============================================================================================
	
	
 		clock_t term[2];
    		term[0] = clock();

		printf("Iniciando Termalizacao. \n\n");
		acao();                         	       // Chama o primeiro valor para a acaoo de gauge;
		termalizacaoHeatBath();		 	       // Faz a termalizacao do sistema atraves de do algoritmo HeatBath; 
		// termalizacaoOver();			       // Faz a termalizacao HeatBath adicionando Overrelaxation.
	
		term[1] = clock();
    		double termTime = (term[1] - term[0])*1.0 / CLOCKS_PER_SEC;
    		printf("Tempo de termalizacao: %g segundos.\n", termTime);
		printf("Tempo de termalizacao: %g minutos. \n\n", termTime/60.0);
		printf("\n");

		// ===========================================================================================
		// Guardar Configuracoes de Gauge
		// ===========================================================================================
		
		saveLattice();
	
						
		tabela = 1.0 - 2.0*S/beta[coupling];
		printf("plaqueta = %lf\n\n", tabela);
	
		
		
		
		
		U = liberarMatrizReal (N, N, N, NT, d, 4, U);
		vd = liberarMatrizInteiro (N, N, N, NT, d, 4, vd);
		ve = liberarMatrizInteiro (N, N, N, NT, d, 4, ve);
	
	}	

free(beta);

Total[1] = clock();
double TotalTime = (Total[1] - Total[0])*1.0 / CLOCKS_PER_SEC;

printf("Tempo gasto: %g segundos.\n", TotalTime);
printf("Tempo gasto: %g minutos.\n", TotalTime/60.0);
printf("Tempo gasto: %g horas. \n", TotalTime/3600.0);
printf("Tempo gasto: %g dias. \n\n", TotalTime/86400.0);


return 0;

}
