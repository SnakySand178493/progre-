#include <stdio.h>

int main(){
    int i;

    for (i=1; i <= 10; i++){
        if(i==5) //En cuanto llega a 5 termina el ciclo por el break
            break;
        printf("i = %i\n", i);
    }
    return 0;
}