#include <stdio.h>	
#include <stdlib.h>


#define  N		          20			    	  // Uma rede 3d com todas as direcoes iguais.
#define  NT       	  	  20			 		  // Direcao temporal da rede.
#define  d                4					  	  // Dimensao do espaaco-tempo.
#define  pi		          3.14159265358979323846  // Numero pi.
#define COMPONENTS 		  4 					  // Define a constante para o número de componentes da matriz SU(2)
#define VOLUME            (N*N*N*NT)              // Define o calculo de volume
#define NORMALIZADOR_PLAQ (6 * N * N * N * NT)

#define CHECK_ALLOC(ptr) \
    if ((ptr) == NULL) { \
        printf("** Erro: Memoria Insuficiente **\n"); \
        return NULL; \
    }



//====================================================================================
// Definindo os arquivos que ser�o utilizados no programa.
//====================================================================================


FILE *gaugelink;



//====================================================================================
// Definindo as vari�veis globais que ser�o utilizadas no programa.
//====================================================================================

double S;												// Valor da acao.
double plaqt;											// Valor da plaqueta.			
int coupling;
int temperatura;														
int observavel;														
int numerobeta;														
														
//====================================================================================
// Definindo os vetores e matrizes do programa. 
//====================================================================================



double *beta;


int ******vd;			// Definindo os vizinhos da direita.
int ******ve;			// Definindo os vizinhos da esquerda.
double ******U;			// Definindo as variaveis de link.

//====================================================================================
// Gerador de numeros aleatorios Ranmar (ranmar.c)
//====================================================================================

double ranmar(void);
void rmarin(int, int);
static double u[97], c, cd, cm;
int i97, j97;
double aleatorio();


//====================================================================================
// Inicializacao do programa (inicializacao.c)
//====================================================================================

void coldStart();

//====================================================================================
// Testes do programa (testes.c)
//====================================================================================

void testeunitario(double a0, double a1, double a2, double a3);

//====================================================================================
// Tabela de vizinhos (vizinhos.c)
//====================================================================================

int* vizinhoPeriDir(const int vector[4], int direction);
int* vizinhoPeriEsq(const int vector[4], int direction);


//====================================================================================
//Produto de matrizes (ProdutoMatrizes.c)
//====================================================================================

void prodMatriz(double e0, double e1, double e2, double e3,
				double f0, double f1, double f2, double f3,
				double *g0, double *g1, double *g2, double *g3);



//====================================================================================
//Acao e plaqueta (Acao.c)
//====================================================================================

double plaqueta(int n1, int n2, int n3, int n4, int mu, int nu);
void acao();

//====================================================================================
// Funcoes para os grampos no calculo de algoritmos de monte carlo (grampos.c)
//====================================================================================

void grampoSuperior(int x, int y, int z, int t, int i, int j, double *e0, double*e1, double *e2, double *e3);
void grampoInferior(int x, int y, int z, int t, int i, int j, double *e0, double*e1, double *e2, double *e3);
void somaGrampos(int x, int y, int z, int t, int i, double *b0, double *b1, double *b2, double *b3);


//====================================================================================
// Funcoes para calculo de banho termico (banhoTermico.c)
//====================================================================================

void banhoTermico(int x, int y, int z, int t, int i, double*f0, double *f1, double *f2, double *f3, double *e0, double *e1, double *e2, double *e3);
double novaacaoHeatBath(int n1, int n2, int n3, int n4, int mu);
void heatSweep();
void termalizacaoHeatBath();

//====================================================================================
//Funcoes para calculo de Overrelaxation  (overRelaxation.c)
//====================================================================================

void overelaxation (int n1, int n2, int n3, int n4, int mu,
		    double u0, double u1, double u2, double u3,
                    double *f0, double *f1, double *f2, double *f3,
                    double *e0, double *e1, double *e2, double *e3);
double novaacaoOver (int n1, int n2, int n3, int n4, int mu);
void overSweep();
void termalizacaoOver();

//====================================================================================
//Funcao que salva configuracoes de rede
//====================================================================================
//
void saveLattice();


//====================================================================================
//Funcoes que criam matrizes grandes com alocacao de memoria
//====================================================================================

void ******alocarMatriz6D(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6);
void *****alocarMatriz5D(size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6);
void ****alocarMatriz4D(size_t dim3, size_t dim4, size_t dim5, size_t dim6);
void ***alocarMatrix3D(size_t dim4, size_t dim5, size_t dim6);
void **alocarMatrix2D(size_t dim5, size_t dim6);
void *alocarMatriz1D(size_t dim6);


void liberarMatriz6D(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6, void ******matrix);
void liberarMatriz5D(size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6, void *****matrix);
void liberarMatriz4D(size_t dim3, size_t dim4, size_t dim5, size_t dim6, void ****matrix);
void liberarMatriz3D(size_t dim4, size_t dim5, size_t dim6, void ***matrix);
void liberarMatriz2D(size_t dim5, size_t dim6, void **matrix);
void liberarMatriz1D(size_t dim6, void *matrix);

void contadorLinhasBeta();

void savePlaq();