#include <stdio.h>
#define MAX 1000000
int main(){
    int array[MAX];
    int n = 0, m = 0;

    printf("Ingresa la cantidad de datos: \n");
    scanf("%d", &n);

    // Leer datos
    for (int i = 0; i < n; i++){
        printf("Ingresa el dato [%d]: ", i);
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n-1; j++){
            if (array[j] > array[j + 1]){
                m = array[j];
                array[j] = array[j + 1];
                array[j + 1] = m;
            }
        }
    }

    // Imprimir
    printf("El arreglo ordenado es:\n[");
    for (int i = 0; i < n; i++){
        printf("%d", array[i]);
        if (i == n - 1)
            continue;
        printf(", ");
    }
    printf("]\n");

    return 0;
}