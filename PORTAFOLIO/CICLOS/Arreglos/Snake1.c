#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 30
#define HEIGHT 15

int x, y; // posición de la primera parte de la vibora
int fruitX, fruitY;
int score;
char input;

/**
 * Función que sirve  para iniciar el juego
 */
void setup(){
    x=WIDTH/2;
    y=HEIGHT/2;

    fruitX = rand()%WIDTH;
    fruitY = rand()%HEIGHT;

    score = 0;
}

void draw(){
    system("clear");
    for(int i=0; i<HEIGHT;i++){
        for(int j=0; j< WIDTH; j++){
            if(j==0 || i ==0 || i==HEIGHT-1 || j == WIDTH-1){
                 printf("#");
                 continue;
            }
            if(x==j && y==i){
                printf("s");
                continue;
            } 
            if(fruitX==j && fruitY==i){
                printf("f");
                continue;
            } 
            printf(" ");
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
    printf("Presiona W o S o D o A\n");
}

void inputFunc(){
    input = getchar();
    getchar();
}

void logic(){
    switch (input){
        case 'w': case 'W': y--; break;
        case 's': case 'S': y++; break;
        case 'a': case 'A': x--; break;
        case 'd': case 'D': x++; break;
    }

    if (x<0 || x>=WIDTH || y<0 || y>=HEIGHT){
        printf("Game over\n");
        exit(0);
    }
}

int main(){
    setup();
    while(true){
        draw();
        inputFunc();
        logic();
    }
    return 0;
}