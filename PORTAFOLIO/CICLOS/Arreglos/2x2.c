#include <stdio.h>
#define TAM 100

void print_array(float array[][TAM], int nr, int nc){
    //lo que está dentro de los parentesis son los parametros (entradas)
    float *ptr=&array[0][0];
    for(int i=0; i<nr*nc;i++){
        //Hay que multiplicar nr*nc para recorrer todos los elementos
        printf("%p \n", (ptr +i));
    }
}

void print_array(float array[][TAM], int nr, int nc){//lo que está dentro de los parentesis son los parametros (entradas)
    float *ptr=&array[0][0];
    printf("[ ");
    for(int i=0; i<nr*nc;i++){
        printf("%f", *(ptr +i));
        if((i+1) % nc == 0) 
            printf("\n");
    }
    printf("] \n");
}

void sumar_matrices(float *a, float *b,  float *c, int nr, int nc) {
    for (int i = 0; i < nc * nr; i++) {
        *(c + i) = *(a + i) + *(b + i);
    }
}

int main(){ 
    float matriz[][TAM]={1.0f, 0.0f, 0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f};// si no fijo tamaños entonces no poner llaves intermedias
    int matInt[][TAM] = {1,0,0,0,1,0,0,0,1};
    //matriz= arreglo bidimensional.
    //no pueden quedarse vacios ambos corchetes de un arreglo bidimensional, solo el primero.
    //f indica flotante, de no ponerse diríamos que es un double.
    float *ptr; //el apuntador tiene el mismo tipo que lo que quiero apuntar.
    //ptr = matriz; //dirección de primer elemento.No usar para matrices.
    ptr = &matriz[0][0]; //dirección del primer elemento. & da la dirección de una variable.
    print_array(matriz, 3, 3);
    return 0;
}