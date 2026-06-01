#include <stdio.h>

int main(){
    int i;

    for (i=1; i <= 10; i++){
        if(i==5) //En cuanto llega a continue no ejecuta todo lo que va despues
            continue;
            printf("i = %i\n", i);
    }
    return 0;
}