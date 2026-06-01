#include <stdio.h>
#define TAM 100

void Leer(float *m, int nr, int nc){
    int j=0;
    for (int i  =0; i < nr*nc; i++){
        printf("Ingresa el valor de M[%d, %d]", i, j++);
        scanf("%f", (m+i));
        if((j) % nc == 0)j = 0;
    }
}

void Escribir(float *m, int nr, int nc){
    for(int i = 0; i < nr*nc; i++){
        printf("%0.2f", *(m+i));
        if((i+1) % nc == 0)
            printf("\n");
    }
}

void Suma(float *a, float *b, float *c, int nr, int nc){
    for(int i = 0; i < nr*nc; i++){
        *(c+i) = *(a+i) + *(b+i);
    }
}

int main(){
    float a[TAM][TAM], b[TAM][TAM], c[TAM][TAM];
    int nrA, ncA, nrB, ncB, nrC, ncC;
    printf("Ingresa el número de columnas y renglones de la primera matriz\n");
    scanf("%i, %i", &nrA, &ncA);
    Leer(&a[0][0],nrA, ncA);
    printf("Ingresa el número de columnas y renglones de la segunda matriz\n");
    scanf("%i, %i", &nrB, &ncB);
    Leer(&b[0][0],nrB, ncB);
    return 0;
}