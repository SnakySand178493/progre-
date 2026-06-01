#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 15
#define MAX_SHOTS 10
#define MAX_ASTEROIDS 3

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
#define GREEN "\033[32m"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

typedef struct { int x, y; bool active; } Shot;
typedef struct { float x, y; float velX, velY; } Asteroid;

int naveX, naveY; 
Shot shots[MAX_SHOTS];
Asteroid asteroids[MAX_ASTEROIDS];

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
    return 0;
}
#else
struct termios oldt;
void enableRawMode(){
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON| ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0); 
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); 
}
void disableRawMode(){ tcsetattr(STDIN_FILENO, TCSANOW, &oldt); }
char readInput(){    
    int ch = getchar();    
    if(ch != EOF) return (char)ch;
    return 0;
}
#endif

void setup(){
    srand(time(NULL));
    naveX = WIDTH / 2;
    naveY = HEIGHT - 3;  
    
    for(int i = 0; i < MAX_SHOTS; i++) shots[i].active = false;

    for(int i = 0; i < MAX_ASTEROIDS; i++) {
        asteroids[i].x = (rand() % (WIDTH - 4)) + 2;
        asteroids[i].y = (rand() % 5) + 1;
        asteroids[i].velX = (rand() % 2 == 0) ? 0.5f : -0.5f; // Velocidad horizontal inicial
        asteroids[i].velY = 0.2f; // Caen lento
    }
}

void updateGame() {
    // Actualizar disparos
    for(int i = 0; i < MAX_SHOTS; i++) {
        if(shots[i].active) {
            shots[i].y--;
            if(shots[i].y <= 0) shots[i].active = false;
        }
    }

    // Actualizar Asteroides
    for(int i = 0; i < MAX_ASTEROIDS; i++) {
        asteroids[i].x += asteroids[i].velX;
        asteroids[i].y += asteroids[i].velY;

        // Rebote en muros laterales
        if(asteroids[i].x <= 1 || asteroids[i].x >= WIDTH - 2) {
            asteroids[i].velX *= -1;
        }

        // Reiniciar si caen al fondo
        if(asteroids[i].y >= HEIGHT - 1) {
            asteroids[i].y = 1;
            asteroids[i].x = (rand() % (WIDTH - 4)) + 2;
        }
    }
}

void draw(){
    clearScreen();
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(j == 0 || i == 0 || i == HEIGHT - 1 || j == WIDTH - 1){
                 printf(YELLOW "▒"); continue;
            }

            // Dibujar Asteroides
            bool drawnAst = false;
            for(int k = 0; k < MAX_ASTEROIDS; k++) {
                if((int)asteroids[k].x == j && (int)asteroids[k].y == i) {
                    printf(GREEN "*"); drawnAst = true; break;
                }
            }
            if(drawnAst) continue;

            // Dibujar Disparos
            bool drawnShot = false;
            for(int k = 0; k < MAX_SHOTS; k++) {
                if(shots[k].active && shots[k].x == j && shots[k].y == i) {
                    printf(RED "!" RESET); drawnShot = true; break;
                }
            }
            if(drawnShot) continue;

            // Dibujar Nave
            if((j == naveX && i == naveY) || 
               (i == naveY + 1 && (j == naveX - 1 || j == naveX + 1))){
                printf(BLUE "#" RESET); continue;
            }

            printf(" ");
        }
        printf("\n");
    }
}

int main(){
    setup();
    #ifndef _WIN32
    enableRawMode();
    #endif

    while(true){
        draw();
        char input = readInput();
        
        if(input == ' ') {
            for(int i = 0; i < MAX_SHOTS; i++) {
                if(!shots[i].active) {
                    shots[i].x = naveX; shots[i].y = naveY - 1;
                    shots[i].active = true; break;
                }
            }
        }
        else if(input != 0){
            switch (input) {
                case 'w': case 'W': if(naveY > 1) naveY--; break;
                case 's': case 'S': if(naveY + 1 < HEIGHT - 2) naveY++; break;
                case 'a': case 'A': if(naveX - 1 > 1) naveX--; break;
                case 'd': case 'D': if(naveX + 1 < WIDTH - 2) naveX++; break;
            }
        }

        updateGame();

        #ifdef _WIN32
        Sleep(50);
        #else
        usleep(50000); 
        #endif
    }

    #ifndef _WIN32
    disableRawMode();
    #endif
    return 0;
}