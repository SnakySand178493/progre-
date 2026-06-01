#include <stdio.h>


#define TAM 1000


void leer_matriz(int mat[][TAM], int m, int n){
   for(int i = 0; i<m; i++){ 
       for (int j=0; j<n;++j){ 
           printf("Ingresa el valor para M [%d, %d]: ", i, j);
           scanf("%d", &mat[i][j]);

       }

   }

}
void mostrar_matriz(int mat[][TAM], int m, int n){
   printf("[\n");
   for(int i = 0; i<m; i++){
       printf("[");
       for (int j=0; j<n;++j){
           printf("%d ", mat[i][j]);
       }
       printf("]\n");
   }
   printf("]\n");
}

void sumar_matrices(int matA[][TAM], int matB[][TAM], int matC[][TAM], int m, int n){
   for(int i = 0; i<m; i++){
       for (int j=0; j<n;++j){
           matC[i][j] = matA[i][j] + matB[i][j];
       }
   }
}

void multiplicar_matrices(int matA[][TAM], int matB[][TAM], int matC[][TAM], int m, int n){
   for(int i = 0; i<m; i++){
       for (int j=0; j<n;++j){
           matC[i][j] = 0;
           for (int k=0; k<n; ++k){
               matC[i][j] += matA[i][k] * matB[k][j];
           }
       }
   }
}

void transponer_matriz(int matA[][TAM], int matB[][TAM], int m, int n){
   for(int i = 0; i<m; i++){
       for (int j=0; j<n;++j){
           matB[j][i] = matA[i][j];
       }
   }
}

   intmain(){
   float A[TAM][TAM], B[TAM][TAM], C[TAM][TAM];
   int fA, cA, fB, cB, opcion;


   printf("Ingrese filas y columnas de la matriz A:\n");
   scanf("%d %d", &fA, &cA);
   float A[fA][cA];


   leer(A, fA, cA);


   printf("Seleccione una operación: \n");
   printf("1. Suma\n");
   printf("2. Multiplicaciòn\n");
   printf("3. Transpuesta\n");
   printf("4. Determinante\n");
   scanf("%d", &opcion);


   switch (opcion){
       case 1:    
           printf("Ingrese filas y columnas de la matriz B:\n");
           scanf("%d %d", &fB, &cB);
           float B[fB][cB];
           if (fA==fB && cA==cB){
               suma(A, B, C, fA, cA);
           }
       }
	
}
