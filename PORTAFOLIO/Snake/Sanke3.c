#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 30
#define HEIGHT 15

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

int snakeX, snakeY; // posición de la primera parte de la vibora
int fruitX, fruitY;
char direction='d';
int score=0;

int increaseScore(){
    static int score=0; //Variables estáticas guardan su valor incluso cuando se termuina la función
    score++;
    return score;
}

void moveSnake(int *x, int *y, char dir){//Prarametros por referencia cuando están como apuntadores, significa que la variable se va a modificar aunque este afuera de la función
    switch (dir){
        case 'w': case 'W': (*y)--; break;
        case 's': case 'S': (*y)++; break;
        case 'a': case 'A': (*x)--; break;
        case 'd': case 'D': (*x)++; break;
    }
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif    
}

#ifdef _WIN32
    char readInput(){
        if(_kbhit()) return _getc();
        return direction;
    }
#else

    struct termios oldt;

    void enableRawMode(){
        struct termios newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        fcntl(STDIN_FILENO, F_GETFL, O_NONBLOCK);
    }

    void disableRawMode(){
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }

    char readInput(){
        int ch;
        ch = getchar();
        if(ch != EOF) return ch;
        return 0;
    }
#endif    

//Función que sirve  para iniciar el juego
void setup(){
    snakeX=WIDTH/2;
    snakeY=HEIGHT/2;

    fruitX = (rand()%(WIDTH-2))+1;
    fruitY = (rand()%(HEIGHT-2))+1;
}

void draw(){
    clearScreen();
    for(int i=0; i<HEIGHT;i++){
        for(int j=0; j< WIDTH; j++){
            if(j==0 || i ==0 || i==HEIGHT-1 || j == WIDTH-1){
                 printf(RESET"#");
                 continue;
            }
            if(snakeX==j && snakeY==i){
                printf(GREEN"s");
                continue;
            } 
            if(fruitX==j && fruitY==i){
                printf(RED"f");
                continue;
            } 
            printf(RESET" ");
        }
        printf(RESET"\n");
    }
    printf(BLUE"Score: %d\n", score);
}

void logic(){
    if (snakeX<=0 || snakeX>=WIDTH || snakeY<=0 || snakeY>=HEIGHT){
        printf("Game over\n");
        exit(0);
    }
    if(snakeX == fruitX && snakeY == fruitY){
        fruitX = (rand()%(WIDTH-2))+1;
        fruitY = (rand()%(HEIGHT-2))+1;
        score = increaseScore();
    }
}

int main(){
    char newDirection;
    setup();
    #ifndef _WIN32
    #endif
    enableRawMode();
    while(true){
        draw();
        newDirection = readInput();
        switch (newDirection){
            case 'w': case 'W': case 's': case 'S': case 'a': case 'A': case 'd': case 'D': 
                direction = newDirection; break;
        }
        moveSnake(&snakeX, &snakeY, direction);
        logic();
        #ifdef _WIN32
            Sleep(150);
        #else
            usleep(150000);
        #endif
    }
    #ifndef _WIN32
    #endif
    disableRawMode();
    return 0;
}