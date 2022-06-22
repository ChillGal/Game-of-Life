#ifndef GAMEOFLIFE_DISPLAY_H
#define GAMEOFLIFE_DISPLAY_H

#include <SDL2/SDL.h>

struct Display{
    int W,H;
    bool running;
    SDL_Window *window;
    SDL_Renderer  *renderer;
};

int initialise_display(int ***cell);
void display_grid();
#endif //GAMEOFLIFE_DISPLAY_H
