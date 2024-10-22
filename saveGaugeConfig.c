#include <stdio.h>
#include "funcoes_SU(2).h"
#include <stdlib.h>

void saveLattice(){

	char filename[200];
	
	if(observavel == 1){
		//================================================================
		// CONFIGURACOES PARA CALCULO DE PLAQUETA OU LOOP DE POLYAKOV
		//================================================================
		
		if(temperatura == 1){

			sprintf(filename, "/home/matheus/codigos_doc/su2/dados_gerados/gauge_config/temperatura_zero/configuracoes_termalizadas/para_calculo_observaveis/N%01d/gauge_conf_N%01d_beta%0.4f.txt", N, N, beta[coupling]);
		
		}else if (temperatura == 2){

			sprintf(filename, "/home/matheus/codigos_doc/su2/dados_gerados/gauge_config/temperatura_finita/configuracoes_termalizadas/para_calculo_observaveis/NT%01d/N%01d/gauge_conf_N%01d_NT%01d_beta%0.4f.txt", NT, N, N, NT, beta[coupling]);
		
		}
	
	}else if(observavel == 2){

		// ===============================================================
    	// PARA CONFIGURACOES PARA FIXACAO DE GAUGE
    	// ===============================================================
    	
		if(temperatura == 1){
		
			 sprintf(filename, "/media/user/Seagate Expansion Drive/su2/dados_gerados/gauge_config/temperatura_zero/configuracoes_termalizadas/para_fixacao_gauge_landau/N%01d/gauge_conf_N%01d_NT%01d_beta%0.7f.txt", N, N, NT, beta[coupling]);
    	
		}else if (temperatura == 2){
		
			sprintf(filename, "/media/user/Seagate Expansion Drive/su2/dados_gerados/gauge_config/temperatura_finita/configuracoes_termalizadas/para_calculo_fixacao_gauge_landau/NT%01d/N%01d/gauge_conf_N%01d_NT%01d_beta%0.7f.txt", NT, N, N, NT, beta[coupling]);
    	
		}
	
	}
    
	gaugelink = fopen(filename, "w+");

	int n1, n2, n3, n4, mu;
	int a;
	
	for (n1 = 0; n1 < N; n1++) {
            	for (n2 = 0; n2 < N; n2++) {
                    	for (n3 = 0; n3 < N; n3++) {
                            	for (n4 = 0; n4 < NT; n4++) {
                                    	for (mu = 0; mu < d; mu++) {
                                            	for (a = 0; a < 4; a++) {
						
													fprintf(gaugelink,"%d %d %d %d %d %d %.12f\n",n1, n2, n3, n4, mu, a, U[n1][n2][n3][n4][mu][a]);
												}
         	                           	}
                            	}
                    	}
            	}
    	}
	
	fclose(gaugelink);

}



