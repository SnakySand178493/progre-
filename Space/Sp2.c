#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 15

#define RED "\033[31m"
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

int naveX, naveY; 
int fruitX, fruitY;

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

void setup(){
    srand(time(NULL));
    // Centrado horizontalmente
    naveX = WIDTH / 2;
    // Posicionado en la parte inferior (dejando espacio para las alas)
    naveY = HEIGHT - 3;  
    
    fruitX = (rand() % (WIDTH - 2)) + 1;
    fruitY = (rand() % (HEIGHT - 2)) + 1;
}

void draw(){
    clearScreen();
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(j == 0 || i == 0 || i == HEIGHT - 1 || j == WIDTH - 1){
                 printf(YELLOW "▒");
                 continue;
            }

            // Dibujar Nave (Punta en naveX, naveY | Alas en naveY + 1)
            if((j == naveX && i == naveY) || 
               (i == naveY + 1 && (j == naveX - 1 || j == naveX + 1))){
                printf(BLUE "#" RESET);
                continue;
            }

            if(j == fruitX && i == fruitY){
                printf(RED "Ѽ" RESET);
                continue;
            } 

            printf(" ");
        }
        printf("\n");
    }
    printf(RESET "Muevete con WASD | Salir: Ctrl+C\n");
}

int main(){
    setup();
    
    #ifndef _WIN32
    enableRawMode();
    #endif

    while(true){
        draw();
        
        char input = readInput();
        
        if(input != 0){
            switch (input) {
                case 'w': case 'W': 
                    if(naveY > 1) naveY--; 
                    break;
                case 's': case 'S': 
                    // Limite inferior considerando el renglón de las alas
                    if(naveY + 1 < HEIGHT - 2) naveY++; 
                    break;
                case 'a': case 'A': 
                    if(naveX - 1 > 1) naveX--; 
                    break;
                case 'd': case 'D': 
                    if(naveX + 1 < WIDTH - 2) naveX++; 
                    break;
            }
        }

        #ifdef _WIN32
        Sleep(30);
        #else
        usleep(30000); 
        #endif
    }

    #ifndef _WIN32
    disableRawMode();
    #endif

    return 0;
}