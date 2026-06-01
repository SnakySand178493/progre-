#include <stdio.h>
#define RED "\033[31m"

int main(int argc, char **argv[]){
    FILE *archivo;

    if (argc < 2) {
        printf(RED"Error FATAL: no se ha proporcionado un archivo\n");
        return 1;
    }

    archivo = fopen(argv[1], "r");

    if (archivo != NULL) {
        printf("Archivo abierto correctamente.\n");
        int res = fclose(archivo);
        printf("fclose = %d\n", res);
    }
        else {
            printf(RED"Error FATAL: %s no es un archivo ni derectorio\n");
        }
        return 0;
}