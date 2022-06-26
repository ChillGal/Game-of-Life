#ifndef GAMEOFLIFE_ENGINE_H
#define GAMEOFLIFE_ENGINE_H

extern int GRIDSIZEX, GRIDSIZEY, maxX, maxY;
extern int ITERATETIME; //Time between iterations
extern _Bool PAUSE; //Pause state
extern struct grid G;
extern struct grid G1;

struct grid { //Grid structure
    int **cell; //Pointer to grid cells
    int sizeX, sizeY; //Size of X and Y
};

int initialise_grid(int ***cell, int SizeX, int SizeY); //Setup grid
//void destroy_grid(int ***cell); //Grid cleanup
void cleanup_memory(); //Memory cleanup
void initialise_engine(); //Setup engine
void iterate_grid(int ***cell, int ***iteratedCell); //Calculate next iteration
void initialise_static_environment(); //Setup static environment
#endif //GAMEOFLIFE_ENGINE_H
