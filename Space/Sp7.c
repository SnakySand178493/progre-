#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 15
#define MAX_SHOTS 10
#define MAX_ITEMS 10 
#define NAVE_SPEED 2  // <--- Cambia este número para ajustar la velocidad

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
bool isPaused = false; 
Shot shots[MAX_SHOTS];
Entity entities[MAX_ITEMS]; 

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
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); 
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
            entities[i].velY = (type == '*') ? 0.2f : 0.3f;
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
    if (isPaused) return;

    frameCounter++;
    if(frameCounter % 40 == 0) spawnEntity('*');
    if(frameCounter % 60 == 0) spawnEntity('+');

    for(int i = 0; i < MAX_SHOTS; i++) {
        if(shots[i].active) {
            shots[i].y--;
            if(shots[i].y <= 0) shots[i].active = false;
        }
    }

    for(int i = 0; i < MAX_ITEMS; i++) {
        if(!entities[i].active) continue;
        entities[i].x += entities[i].velX;
        entities[i].y += entities[i].velY;
        if(entities[i].x <= 1 || entities[i].x >= WIDTH - 2) entities[i].velX *= -1;
        if(entities[i].y >= HEIGHT - 1) entities[i].active = false;

        int ex = (int)entities[i].x;
        int ey = (int)entities[i].y;

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

        for(int j = 0; j < MAX_SHOTS; j++) {
            if(shots[j].active && shots[j].x == ex && shots[j].y == ey) {
                shots[j].active = false;
                entities[i].active = false;
                score += (entities[i].type == '*') ? 10 : 1;
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
            for(int k = 0; k < MAX_ITEMS; k++) {
                if(entities[k].active && (int)entities[k].x == j && (int)entities[k].y == i) {
                    if(entities[k].type == '*') printf(GREEN "*");
                    else printf(MAGENTA "+"); 
                    drawn = true; break;
                }
            }
            if(drawn) continue;

            for(int k = 0; k < MAX_SHOTS; k++) {
                if(shots[k].active && shots[k].x == j && shots[k].y == i) {
                    printf(RED "!" RESET); drawn = true; break;
                }
            }
            if(drawn) continue;

            if((j == naveX && i == naveY) || (i == naveY + 1 && (j == naveX - 1 || j == naveX + 1)))
                { printf(BLUE "#" RESET); continue; }

            printf(" ");
        }
        printf("\n");
    }
    if (isPaused) printf(YELLOW " [ PAUSA ]\n" RESET);
    else printf(RESET " SCORE: %-4d | WASD: Mover | P: Pausa\n", score);
}

int main(){
    setup();
    #ifndef _WIN32
    enableRawMode();
    #endif

    while(true){
        draw();
        char input = readInput();
        
        if(input == 'p' || input == 'P') isPaused = !isPaused;

        if (!isPaused) {
            if(input == ' ') {
                for(int i = 0; i < MAX_SHOTS; i++) {
                    if(!shots[i].active) {
                        shots[i].x = naveX; shots[i].y = naveY - 1;
                        shots[i].active = true; break;
                    }
                }
            } else if(input != 0){
                switch (input) {
                    // Ahora sumamos/restamos NAVE_SPEED para movernos más rápido
                    case 'a': case 'A': 
                        if(naveX - NAVE_SPEED > 1) naveX -= NAVE_SPEED; 
                        else naveX = 2; // Asegura que no atraviese el muro
                        break;
                    case 'd': case 'D': 
                        if(naveX + NAVE_SPEED < WIDTH - 2) naveX += NAVE_SPEED; 
                        else naveX = WIDTH - 3;
                        break;
                    case 'w': case 'W': 
                        if(naveY - NAVE_SPEED > 1) naveY -= NAVE_SPEED; 
                        else naveY = 2;
                        break;
                    case 's': case 'S': 
                        if(naveY + NAVE_SPEED < HEIGHT - 2) naveY += NAVE_SPEED; 
                        else naveY = HEIGHT - 3;
                        break;
                }
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