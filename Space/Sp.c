#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

int snakeX, snakeY; 
int fruitX, fruitY;
char direction = 'w';
int score = 0;
bool game_over = false;

void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#ifdef _WIN32
char readInput(){
    if(_kbhit()) return _getch();
    return direction;
}
#else
struct termios oldt;
void enableRawMode(){
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON| ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    
    int flags = fcntl(STDIN_FILENO, F_GETFL, O_NONBLOCK); 
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); 
}
void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
char readInput(){    
    int ch = getchar();    
    if(ch != EOF) return ch;
    return 0;
}
#endif

void generateFruit(){
    // La fruta no debe aparecer en los bordes
    fruitX = (rand() % (WIDTH - 2)) + 1;
    fruitY = (rand() % (HEIGHT - 2)) + 1;
}

void setup(){
    srand(time(NULL));
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;  
    generateFruit();  
}

void draw(){
    clearScreen();
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            // 1. Bordes
            if(j == 0 || i == 0 || i == HEIGHT - 1 || j == WIDTH - 1){
                 printf(YELLOW "▒");
                 continue;
            }

            // 2. Dibujar Nave (Punta en snakeX, snakeY | Alas en snakeY + 1)
            if((j == snakeX && i == snakeY) ||           // Punta
               (j == snakeX - 1 && i == snakeY + 1) ||   // Ala izquierda
               (j == snakeX + 1 && i == snakeY + 1)){    // Ala derecha
                printf(BLUE "#" RESET);
                continue;
            } 

            // 3. Fruta/Objetivo
            if(j == fruitX && i == fruitY){
                printf(RED "Ѽ" RESET);
                continue;
            } 

            printf(" ");
        }
        printf("\n");
    }
    printf(RESET "Score: %d | Controles: W,A,S,D\n", score);
}

void logic(){
    // Mover la nave según la dirección
    switch (direction) {
        case 'w': case 'W': snakeY--; break;
        case 's': case 'S': snakeY++; break;
        case 'a': case 'A': snakeX--; break;
        case 'd': case 'D': snakeX++; break;
    }

    // Colisiones con el muro considerando el cuerpo de la nave
    // Checamos punta (snakeY) y alas (snakeY + 1)
    if(snakeX - 1 <= 0 || snakeX + 1 >= WIDTH - 1 || 
       snakeY <= 0 || snakeY + 1 >= HEIGHT - 1){
        game_over = true;
    }

    // Colisiones con la fruta (cualquier parte de la nave puede recolectarla)
    if((snakeX == fruitX && snakeY == fruitY) || 
       (snakeX - 1 == fruitX && snakeY + 1 == fruitY) || 
       (snakeX + 1 == fruitX && snakeY + 1 == fruitY)){        
        score += 10;
        generateFruit();
    }
}

int main(){
    setup();
    #ifndef _WIN32
    enableRawMode();
    #endif

    while(!game_over){
        draw();
        char input = readInput();
        if(input != 0) direction = input;

        logic();

        #ifdef _WIN32
        Sleep(100);
        #else
        usleep(150000); // 0.15 segundos
        #endif
    }

    clearScreen();
    printf("GAME OVER\nFinal Score: %d\n", score);

    #ifndef _WIN32
    disableRawMode();
    #endif
    return 0;
}