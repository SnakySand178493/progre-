#include <stdio.h>

int main(){
    FILE *archivo;
    archivo = fopen("datos.txt", "a");

    if(archivo == NULL){
        printf("Error fatal: datos.txt No es un archivo o carpeta\n");
        return 1;
    }

    fprintf(archivo, "Alfonso\t20\t0\n");
    fprintf(archivo, "Nepamuceno\t42\t0\n");
    fclose(archivo); //Cierra el archivo que se ha abierto previamente con fopen().
    return 0;
}
//Archivos de texto plano (.txt)