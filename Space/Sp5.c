#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 15
#define MAX_SHOTS 10
#define MAX_ASTEROIDS 4 // Aumentamos un poco la dificultad

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

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
int score = 0;
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

void resetAsteroid(int i) {
    asteroids[i].y = 1;
    asteroids[i].x = (rand() % (WIDTH - 4)) + 2;
    asteroids[i].velX = ((rand() % 100) / 100.0f) - 0.5f; // Dirección aleatoria
    asteroids[i].velY = ((rand() % 10) / 50.0f) + 0.1f;  // Velocidad aleatoria
}

void setup(){
    srand(time(NULL));
    naveX = WIDTH / 2;
    naveY = HEIGHT - 3;  
    for(int i = 0; i < MAX_SHOTS; i++) shots[i].active = false;
    for(int i = 0; i < MAX_ASTEROIDS; i++) resetAsteroid(i);
}

void updateGame() {
    // 1. Actualizar Disparos
    for(int i = 0; i < MAX_SHOTS; i++) {
        if(shots[i].active) {
            shots[i].y--;
            if(shots[i].y <= 0) shots[i].active = false;
        }
    }

    // 2. Actualizar Asteroides y Colisiones
    for(int i = 0; i < MAX_ASTEROIDS; i++) {
        asteroids[i].x += asteroids[i].velX;
        asteroids[i].y += asteroids[i].velY;

        // Rebote en muros
        if(asteroids[i].x <= 1 || asteroids[i].x >= WIDTH - 2) asteroids[i].velX *= -1;

        // Reiniciar si salen por abajo
        if(asteroids[i].y >= HEIGHT - 1) resetAsteroid(i);

        int ax = (int)asteroids[i].x;
        int ay = (int)asteroids[i].y;

        // --- DETECCIÓN DE COLISIONES ---

        // A. ¿Asteroide toca a la Nave? (Punta o Alas)
        bool hitNave = (ax == naveX && ay == naveY) || 
                       (ay == naveY + 1 && (ax == naveX - 1 || ax == naveX + 1));
        
        if(hitNave) {
            clearScreen();
            printf(RED "\n\n   !!! GAME OVER !!!\n");
            printf(YELLOW "   Tu nave fue destruida.\n");
            printf(RESET "   Puntuacion final: %d\n\n", score);
            #ifndef _WIN32
            disableRawMode();
            #endif
            exit(0);
        }

        // B. ¿Disparo toca a un Asteroide?
        for(int j = 0; j < MAX_SHOTS; j++) {
            if(shots[j].active && shots[j].x == ax && shots[j].y == ay) {
                shots[j].active = false;
                resetAsteroid(i); // El asteroide "muere" y reaparece arriba
                score += 10;
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

            // Dibujar Asteroides
            bool drawn = false;
            for(int k = 0; k < MAX_ASTEROIDS; k++) {
                if((int)asteroids[k].x == j && (int)asteroids[k].y == i) {
                    printf(GREEN "*"); drawn = true; break;
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
            if((j == naveX && i == naveY) || 
               (i == naveY + 1 && (j == naveX - 1 || j == naveX + 1))){
                printf(BLUE "#" RESET); continue;
            }
            printf(" ");
        }
        printf("\n");
    }
    printf(RESET "SCORE: %d | ESPACIO: Disparar\n", score);
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
    return 0;
}