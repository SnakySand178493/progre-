#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Error %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Hola Mundo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0
    );

    if(!window){
        printf("Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!renderer){
        printf("Error Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while(running){

        // Revisar eventos
        while(SDL_PollEvent(&event)){

            // Si se presiona la X de la ventana
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        // Fondo negro
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Color blanco
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Cuadrado centrado
        SDL_Rect square = {
            375,
            275,
            50,
            50
        };

        SDL_RenderFillRect(renderer, &square);

        // Mostrar
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}