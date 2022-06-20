#ifndef GAMEOFLIFE_ENGINE_H
#define GAMEOFLIFE_ENGINE_H

extern int ITERATETIME; //Time between iterations
extern bool pause; //Pause state

struct grid { //Grid structure
int **cell; //Pointer to grid cells
int sizeX, sizeY; //Size of X and Y
};



int initialise_grid(); //Setup grid
void destroy_grid(int ***cell); //Grid cleanup
void cleanup_memory(); //Memory cleanup
void initialise_engine(); //Setup engine
void iterate_grid(int ***cell, int ***iteratedCell);
#endif //GAMEOFLIFE_ENGINE_H
