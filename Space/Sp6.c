#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 15
#define MAX_SHOTS 10
#define MAX_ITEMS 10 // Máximo de objetos en pantalla

#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#define RESET   "\033[0m"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

typedef struct { int x, y; bool active; } Shot;
typedef struct { float x, y; float velX, velY; bool active; char type; } Entity;

int naveX, naveY, score = 0;
long frameCounter = 0;
Shot shots[MAX_SHOTS];
Entity entities[MAX_ITEMS]; // Asteroides '*' y Estrellas 's'

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

#ifdef _WIN32
char readInput(){ if(_kbhit()) return _getch(); return 0; }
#else
struct termios oldt;
void enableRawMode(){
    struct termios newt; tcgetattr(STDIN_FILENO, &oldt); newt = oldt;
    newt.c_lflag &= ~(ICANON| ECHO); tcsetattr(STDIN_FILENO, TCSANOW, &newt);    
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK); 
}
void disableRawMode(){ tcsetattr(STDIN_FILENO, TCSANOW, &oldt); }
char readInput(){ int ch = getchar(); if(ch != EOF) return (char)ch; return 0; }
#endif

void spawnEntity(char type) {
    for(int i = 0; i < MAX_ITEMS; i++) {
        if(!entities[i].active) {
            entities[i].active = true;
            entities[i].type = type;
            entities[i].x = (rand() % (WIDTH - 4)) + 2;
            entities[i].y = 1;
            entities[i].velX = ((rand() % 100) / 200.0f) - 0.25f;
            entities[i].velY = (type == '*') ? 0.2f : 0.3f; // Estrellas bajan un poco más rápido
            break;
        }
    }
}

void setup(){
    srand(time(NULL));
    naveX = WIDTH / 2; naveY = HEIGHT - 3;  
    for(int i = 0; i < MAX_SHOTS; i++) shots[i].active = false;
    for(int i = 0; i < MAX_ITEMS; i++) entities[i].active = false;
}

void updateGame() {
    frameCounter++;

    // Generar Asteroide cada 2 segundos (2000ms / 50ms = 40 frames)
    if(frameCounter % 40 == 0) spawnEntity('*');
    
    // Generar Estrella cada 3 segundos (3000ms / 50ms = 60 frames)
    if(frameCounter % 60 == 0) spawnEntity('+');

    // Actualizar Disparos
    for(int i = 0; i < MAX_SHOTS; i++) {
        if(shots[i].active) {
            shots[i].y--;
            if(shots[i].y <= 0) shots[i].active = false;
        }
    }

    // Actualizar Entidades (Asteroides y Estrellas)
    for(int i = 0; i < MAX_ITEMS; i++) {
        if(!entities[i].active) continue;

        entities[i].x += entities[i].velX;
        entities[i].y += entities[i].velY;

        if(entities[i].x <= 1 || entities[i].x >= WIDTH - 2) entities[i].velX *= -1;
        if(entities[i].y >= HEIGHT - 1) entities[i].active = false;

        int ex = (int)entities[i].x;
        int ey = (int)entities[i].y;

        // Colisión con Nave
        if((ex == naveX && ey == naveY) || (ey == naveY + 1 && (ex == naveX - 1 || ex == naveX + 1))) {
            if(entities[i].type == '*') {
                clearScreen();
                printf(RED "\n   !!! GAME OVER !!!\n" RESET "   Puntuacion: %d\n", score);
                #ifndef _WIN32
                disableRawMode();
                #endif
                exit(0);
            }
        }

        // Colisión con Disparos
        for(int j = 0; j < MAX_SHOTS; j++) {
            if(shots[j].active && shots[j].x == ex && shots[j].y == ey) {
                shots[j].active = false;
                entities[i].active = false;
                score += (entities[i].type == '*') ? 10 : 1; // Asteroide 10pts, Estrella 1pt
            }
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

            bool drawn = false;
            // Dibujar Entidades
            for(int k = 0; k < MAX_ITEMS; k++) {
                if(entities[k].active && (int)entities[k].x == j && (int)entities[k].y == i) {
                    if(entities[k].type == '*') printf(GREEN "*");
                    else printf(MAGENTA "s"); 
                    drawn = true; break;
                }
            }
            if(drawn) continue;

            // Dibujar Disparos
            for(int k = 0; k < MAX_SHOTS; k++) {
                if(shots[k].active && shots[k].x == j && shots[k].y == i) {
                    printf(RED "!" RESET); drawn = true; break;
                }
            }
            if(drawn) continue;

            // Dibujar Nave
            if((j == naveX && i == naveY) || (i == naveY + 1 && (j == naveX - 1 || j == naveX + 1)))
                { printf(BLUE "#" RESET); continue; }

            printf(" ");
        }
        printf("\n");
    }
    printf(RESET "SCORE: %-4d | *: 10pts | s: 1pt\n", score);
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
        } else if(input != 0){
            switch (input) {
                case 'a': case 'A': if(naveX - 1 > 1) naveX--; break;
                case 'd': case 'D': if(naveX + 1 < WIDTH - 2) naveX++; break;
                case 'w': case 'W': if(naveY > 1) naveY--; break;
                case 's': case 'S': if(naveY + 1 < HEIGHT - 2) naveY++; break;
            }
        }
        updateGame();
        #ifdef _WIN32
        Sleep(50);
        #else
        usleep(50000); 
        #endif
    }
    return 0;
}
