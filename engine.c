#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include "engine.h"

//Variables
int GRIDSIZEX = 160; //Grid X size
int GRIDSIZEY = 90; //Grid Y size
int ITERATETIME = 10; //Time between iterations in ms
bool pause = false; //Pause state
struct grid G; //Main grid
struct grid G1; //Next step grid

//Create grid using 2D array using pointers
int initialise_grid(int ***cell, int SizeX, int SizeY) {
    *cell = malloc(sizeof(int)* SizeX); //Allocate memory to vertical columns
    if (*cell == NULL) { //Check that memory has been allocated
        printf("Error occurred allocating memory to vertical columns.\n");
        return 1;
    }
    for (int i=0; i<SizeX; i++){
        *cell[i] = malloc(sizeof(int) * SizeY); //Allocate memory to horizontal rows
        if ((*cell)[i] == NULL){
            printf("Error occurred allocating memory to horizontal rows.\n");
            return 1;
        }
    }
    return 0;
}

//Calculate the next step of the grid
void iterate_grid(int ***cell, int ***iteratedCell) {
//TODO iterate grid function
}

//Clear allocated memory of cells
void destroy_grid(int ***cell) {
    free(**cell);
    free(*cell);
}

//Clear allocated memory of the grids
void cleanup_memory() {
    free(&G.cell); //Clear main grid memory
    free(&G1.cell); //Clear iterative grid memory
}

//Setup the game engine
void initialise_engine() {
    pause = false; //Initial state is not paused
    G.sizeX = G1.sizeX = GRIDSIZEX - 1; //Grid X size
    G.sizeY = G1.sizeY = GRIDSIZEY - 1; //Grid Y size
    initialise_grid(&G.cell, G.sizeX, G.sizeY);
    initialise_grid(&G1.cell, G1.sizeX, G1.sizeY);
    //TODO Initialise display function
}