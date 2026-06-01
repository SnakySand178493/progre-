#include <stdio.h>

int main(){
    FILE *archivo;
    archivo = fopen("datos.txt", "r");

    if(archivo == NULL){
        printf("Error fatal: datos.txt No es un archivo o carpeta\n");
        return 1;
    }

    char c;
    c = getc(archivo);    //getchar(); Obtiene una entrada estandar (del teclado, stdin), salida estándar (en la pantalla, stdout)
    while (c != EOF){ //EOF es una constante que indica el fin del archivo.
        printf("%c", c);
        c = getc(archivo); //getc(); Obtiene un caracter de un archivo, el cual se pasa como argumento a la función. 
    }
    printf("\n");
    fclose(archivo); //Cierra el archivo que se ha abierto previamente con fopen().
    return 0;
}