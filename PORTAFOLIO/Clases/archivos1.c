#include <stdio.h>

int main(){
    FILE *archivo;
    archivo = fopen("datos.txt", "r");

    if(archivo == NULL){
        printf("No se pudo abrir el archivo\n");
        return 1;
    }
    fprintf(archivo, "Alfonso\t20\n");
}