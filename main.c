#include <stdio.h>
#include "SDL-mirror/include/SDL.h"

static int init(SDL_Window **window, SDL_Surface **windowSurface, SDL_Renderer **renderer, int width, int height) {
    int success = 1;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = 0;
    }
    else {
        //Create window
        *window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
        if( *window == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = 0;
        }
        else {
            //Get window surface
            *windowSurface = SDL_GetWindowSurface( *window );
            printf("%p\n", renderer);
            *renderer = (SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

            printf("%p\n", renderer);
            if(*renderer == NULL) {
                fprintf(stderr, "%s", SDL_GetError());
            }
        }
    } return success;
}

int loadMedia(SDL_Surface **surface, char *location) {
    int success = 1;

    *surface = SDL_LoadBMP(location);
    if(*surface == NULL) {
        fprintf(stderr, "Unable to open %s : SDL error : %s", location, SDL_GetError());
        success = 0;
    }

    return success;
}

void freeSurface(SDL_Surface **surface) {
    SDL_FreeSurface(*surface);
}

void destroyAndQuit(SDL_Window **window) {
    SDL_DestroyWindow(*window);

    SDL_Quit();
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

int main(int argc, char** argv)
{
    SDL_Window *window = NULL;
    SDL_Surface *windowSurface = NULL, *helloWorld = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;

    printf("%p\n", renderer);

    if(!init(&window, &windowSurface, &renderer, 800, 600)) {
        printf("Failed to initialize!");
        return -1;
    }

    printf("%p\n", renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    if(!loadMedia(&helloWorld, "sdllogo.bmp")) {
        printf("Failed to load media!");
        return -1;
    }
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, helloWorld);
    if(texture == NULL)
        fprintf(stderr, "failed to create texture : %s", SDL_GetError());

    printf("%p\n", renderer);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    //Added some delay to see stuff
    SDL_Delay(3000);
    //remove the previous line and make a while loop for main


    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    destroyAndQuit(&window);

    return 0;
}