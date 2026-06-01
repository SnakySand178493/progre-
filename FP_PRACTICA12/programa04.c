#include <stdio.h>
#define RED "\033[31m"

int main(int argc, char **argv){
    FILE *archivo;
    char linea[]="Esta linea se agrego mediante la funcion fputs\nAJMPRO\n";

    if(argc < 2){
        printf(RED "Error fatal: hacen falta rgumentos\n");
        return 1;
    }
    
    archivo=fopen(argv[1], "a+");
    
    if(archivo!=NULL){
        printf("el archivo se abrio correctamente\n");
        //while(feof(archivo)==0){
            fputs(linea,archivo);
         //   printf("%s", linea);
        //}
        int res = fclose(archivo);
        printf("fclose=%d\n", res);
    }else{
        printf(RED"Error Fatal: %s no es un archivo o directorio\n", argv[1]);
     }
     return 0;
}