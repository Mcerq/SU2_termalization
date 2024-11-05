#include <stdio.h>
#include <stdlib.h>
#include "funcoes_SU(2).h"


void ******alocarMatriz6D(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6){


	void ******matrix = malloc(dim1 * sizeof(void *****));
	CHECK_ALLOC(matrix);

	for (size_t i = 0; i < dim1; i++){

		matrix[i] = alocarMatriz5D(dim2, dim3, dim4, dim5, dim6);
		
		if(matrix[i] == NULL){

			liberarMatriz6D(i, dim2, dim3, dim4, dim5, dim6, matrix);
			return NULL;
		}

	}

	return matrix;

}

void *****alocarMatriz5D(size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6){

	void *****matrix = malloc(dim2 * sizeof(void ****));
	CHECK_ALLOC(matrix);

	for(size_t i = 0; i < dim2; i++){

		matrix[i] = alocarMatriz4D(dim3, dim4, dim5, dim6);
		
		if(matrix[i] == NULL){
			
			liberarMatriz5D(i, dim3, dim4, dim5, dim6, matrix);
			return NULL;
		}

	}

	return matrix;

}


void ****alocarMatriz4D(size_t dim3, size_t dim4, size_t dim5, size_t dim6){

	void ****matrix = malloc(dim3 * sizeof(void ***));
	CHECK_ALLOC(matrix);

	for(size_t i = 0; i < dim3; i++){

		matrix[i] = alocarMatriz3D(dim4, dim5, dim6);
		
		if(matrix[i] == NULL){

			liberarMatriz4D(i, dim4, dim5, dim6, matrix);
			return NULL;
		}


	}

	return matrix;

}

void ***alocarMatriz3D(size_t dim4, size_t dim5, size_t dim6){

	void ***matrix = malloc(dim4 * sizeof(void **));
	CHECK_ALLOC(matrix);

	for(size_t i = 0; i < dim4; i++){

		matrix[i] = alocarMatriz2D(dim5, dim6);

		if(matrix[i] == NULL){

			liberarMatriz3D(i, dim5, dim6, matrix);
			return NULL;
		}		

	}

	return matrix;

}


void **alocarMatrix2D(size_t dim5, size_t dim6){

	void **matrix = malloc(dim5 * sizeof(void *));
	CHECK_ALLOC(matrix);

	for(size_t i = 0; i< dim5; i++){

		matrix[i] = alocarMatriz1D(dim6);

		if(matrix[i] == NULL) {

			liberarMatriz2D(i, dim6, matrix);
			return NULL;
		}

	}

	return matrix;
}

void *alocarMatriz1D(size_t dim6){

	void *matrix = malloc(dim6 * sizeof(int));
	CHECK_ALLOC(matrix);

	return matrix;
}


void liberarMatriz6D(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6, void ******matrix) {
    
	for (size_t i = 0; i < dim1; i++) {

        liberarMatriz5D(dim2, dim3, dim4, dim5, dim6, matrix[i]);
    }
    
	free(matrix);
}


void liberarMatriz5D(size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6, void *****matrix) {

    for (size_t i = 0; i < dim2; i++) {

        liberarMatriz4D(dim3, dim4, dim5, dim6, matrix[i]);
    }

    free(matrix);
}


void liberarMatriz4D(size_t dim3, size_t dim4, size_t dim5, size_t dim6, void ****matrix) {
    
	for (size_t i = 0; i < dim3; i++) {
    
	    liberarMatriz3D(dim4, dim5, dim6, matrix[i]);
    
	}
    
	free(matrix);
}


void liberarMatriz3D(size_t dim4, size_t dim5, size_t dim6, void ***matrix) {
    
	for (size_t i = 0; i < dim4; i++) {
 
        liberarMatriz2D(dim5, dim6, matrix[i]);
 
    }
 
    free(matrix);
}


void liberarMatriz2D(size_t dim5, size_t dim6, void **matrix) {

    for (size_t i = 0; i < dim5; i++) {

        free(matrix[i]);

    }

    free(matrix);

}

void liberarMatriz1D(size_t dim6, void *matrix) {

    free(matrix);

}