#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "display.h"
#include "engine.h"

#define CELL_SIZE 10 //Size of the cell in pixels

struct Display Dp = {0}; // Display

void colour_background(){    //Set background colour to black
    SDL_SetRenderDrawColor(Dp.renderer, 0,0,0, 255); //Set to black
    SDL_RenderClear(Dp.renderer); //Flush the render buffer
}

//Cleanup allocated memory for window and renderer
void cleanup_display(){
    SDL_DestroyWindow(Dp.window); //Clear allocated memory for window
    SDL_DestroyRenderer(Dp.renderer); //Clear allocated memory for renderer
}

//Show the grid
void display_grid() {
    SDL_SetRenderDrawColor(Dp.renderer, 50, 50, 50, 255); //Set the colour of the grid line
    for (int x = 0; x < ((GRIDSIZEX * CELL_SIZE) + 1); x += CELL_SIZE){ //Creates the horizontal grid lines
        SDL_RenderDrawLine(Dp.renderer,x,0,x,Dp.H);
    }
    for (int y = 0; y < ((GRIDSIZEY * CELL_SIZE) + 1); y += CELL_SIZE){ //Creates the vertical grid lines
        SDL_RenderDrawLine(Dp.renderer,0,y,Dp.W, y);
    }
    SDL_RaiseWindow(Dp.window);
}

//Show live cells on grid
void display_live_cells(int ***cell) {
    for (int i = 0; i < GRIDSIZEX; i++){
        for (int j = 0; j < GRIDSIZEY; j++ ){
            SDL_Rect rect;
            rect.w = CELL_SIZE - 1;
            rect.h = CELL_SIZE - 1;
            rect.x = i * CELL_SIZE + 1;
            rect.y = j * CELL_SIZE + 1;
            if ((*cell)[i][j] == 1){
                SDL_SetRenderDrawColor(Dp.renderer,255,255,255,255);
                SDL_RenderFillRect(Dp.renderer, &rect);
            }
            else if ((*cell)[i][j] == 0) {
                SDL_SetRenderDrawColor(Dp.renderer,0,0,0,0);
                SDL_RenderFillRect(Dp.renderer, &rect);
            }
        }
    }
}

//Update the display
void update_display() {
    int mouseX, mouseY;
    while(Dp.running) {
        //Event detection
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            PAUSE = !PAUSE;
                            break;
                        case SDLK_ESCAPE:
                            Dp.running = false;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN: //SELECT CELL USING CURSOR
                    mouseX = ((event.motion.x / CELL_SIZE));
                    mouseY = ((event.motion.y / CELL_SIZE));
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        (G.cell)[mouseX][mouseY] = 1;
                    } else if (event.button.button == SDL_BUTTON_RIGHT) {
                        (G.cell)[mouseX][mouseY] = 0;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    //This handles cursor leaving and moving back over window
                    /* if (event.window.event == SDL_WINDOWEVENT_ENTER){
                        PAUSE = false;
                    }
                    else if (event.window.event == SDL_WINDOWEVENT_LEAVE){
                        PAUSE = true;
                    }*/
                    break;
                case SDL_QUIT:
                    Dp.running = false;
                    cleanup_display();
                    break;
                default:break;
            }
        }
        if (!PAUSE){
            iterate_grid(&G.cell, &G1.cell);
        }
        display_live_cells(&G.cell); //Creates live cells from the grid G.cell
        SDL_Delay(ITERATETIME);
        SDL_RenderPresent(Dp.renderer); //Render to the window
    }
}

int initialise_display(int ***cell) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //initialise SDL
        printf("Error initializing SDL! %s\n", SDL_GetError());
        return 1; //returns 1 if SDL fails to initialize
    }
    Dp.W = GRIDSIZEX * CELL_SIZE;
    Dp.H = GRIDSIZEY * CELL_SIZE;
    Dp.window = NULL;
    Dp.renderer = NULL;
    if (SDL_CreateWindowAndRenderer(Dp.W, Dp.H, 0, &Dp.window, &Dp.renderer) < 0) { //Check window and renderer created properly
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating display : %s", SDL_GetError());
        return 0;
    }
    Dp.running = true;
    SDL_SetWindowTitle(Dp.window, "Conway's Game of life in C - Written by Jen"); //Set Title of the window
    colour_background(); //set colour of the background
    display_grid(); //Show the grid
    update_display();
    if (Dp.running == false) {
        //Quit SDL subsystems
        SDL_Quit();
    }
}