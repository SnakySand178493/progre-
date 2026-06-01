#include <stdio.h>
#define RED "\033[31m"

int main(){
    FILE *archivo;

    archivo = fopen("datos.txt", "r");

    if (archivo != NULL) {
        printf("Archivo abierto correctamente.\n");
        int res = fclose(archivo);
        printf("fclose = %d\n", res);
    }
        else {
            printf(RED"Error FATAL: no es un archivo ni derectorio\n");
        }
        return 0;
}