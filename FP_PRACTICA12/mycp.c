#include <stdio.h>
#include <string.h>

#define RED "\033[31m"

int main(int argc, char **argv){
    FILE *origen, *destino;
char linea [256];
    
    if(argc < 3){
        printf(RED "Error fatal: hacen falta rgumentos\n");
        return 1;
    }
    if(strcmp(argv[1], argv[2])==0){
        printf(RED"Error Fatal: el origen es el mismo que el destino\n");
        return 1;
    }
    
    origen=fopen(argv[1], "r");

    if(origen!=NULL){
        destino=fopen(argv[2], "w");

        while(feof(origen)==0){
            fgets(linea, 256, origen);
            fputs(linea, destino);
        }
        int res= fclose(origen);
        fclose(destino);
    
    }else{
        printf(RED"Error Fatal: %s no es un archivo o directorio\n", argv[1]);
     }
     return 0;
    }