#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include "engine.h"
#include "display.h"

//Global Variables
int GRIDSIZEX = 160; //Grid X size
int GRIDSIZEY = 90; //Grid Y size
int ITERATETIME = 10; //Time between iterations in ms
bool PAUSE = false; //Pause state
struct grid G; //Main grid
struct grid G1; //Next step grid

//Create grid using 2D array using pointers
int initialise_grid(int ***cell, int SizeX, int SizeY) {

    *cell = malloc(sizeof(int) * SizeX); //Allocate memory to vertical columns
    if ((*cell) == NULL) { //Check that memory has been allocated
        printf("Error occurred allocating memory to vertical columns.\n");
        return 1;
    }
    for (int i = 0; i < SizeX; i++){
        (*cell)[i] = malloc(sizeof(int) * SizeY); //Allocate memory to horizontal rows
        if ((*cell)[i] == NULL){
            printf("Error occurred allocating memory to horizontal rows.\n");
            return 1;
        }
    }
    //Fill grid with 0's
    for (int x = 0; x < SizeX; x++){
        for (int y = 0; y < SizeY; y++) {
            (*cell)[x][y] = 0;
        }
    }
    return 0;
}

//Check number of neighbours around a given cell excluding the edges of the grid
int check_neighbours(int i, int j,int ***cell) {
    int neighbourCount = 0;
    for (int x = -1; x < 2; x++) { //Counting live neighbours around cell coordinate
        for (int y = -1; y < 2; y++) {
            if (*cell[i + x][j + y] == 1) {
                neighbourCount++;
            }
        }
    }
    if (*cell[i][j] == 1 ) {
        return neighbourCount - 1; //Don't count the middle cell
    }
    return neighbourCount;
}

//Check the edges of the grid with toroidal shape (donut shape)
int edge_check_neighbours(int i, int j, int ***cell) {
    int neighbourCount = 0;
    if (i == 0) {
        //Left corner checks
        if (j == 0) { //Top left corner
            if ((*cell[G.sizeX - 1][G.sizeY - 1] == 1) || (*cell[i][GRIDSIZEY - 1] == 1) || (*cell[i + 1][j - 1] == 1)) { //Top row
                neighbourCount++;
            }
            if ((*cell[GRIDSIZEX - 1][j] == 1) || (*cell[i][j] == 1) || (*cell[i + 1][j + 1] == 1)) { //Middle row
                neighbourCount++;
            }
            if ((*cell[GRIDSIZEX - 1][j + 1] == 1) || (*cell[i][j + 1] == 1) || (*cell[i + 1][j + 1] == 1)) { //Bottom row
                neighbourCount++;
            }
        }
        else if (j == GRIDSIZEY - 1) { //Bottom left corner
            if ((*cell[GRIDSIZEX - 1][j - 1] == 1) || (*cell[i][j - 1] == 1) || (*cell[i + 1][j - 1] == 1)) { //Top row
                neighbourCount++;
            }
            if ((*cell[GRIDSIZEX - 1][j] == 1) || (*cell[i][j] == 1) || (*cell[i + 1][j] == 1)) { //Middle row
                neighbourCount++;
            }
            if ((*cell[GRIDSIZEX - 1][0] == 1) || (*cell[i][0] == 1) || (*cell[i + 1][0] == 1)) { //Bottom row
                neighbourCount++;
            }
        }
        else { //Check along the top x border
            for (int x = -1; x < 2; x++) {
                if (*cell[i + x][GRIDSIZEY - 1] == 1) { //Checks top row - connected to bottom border
                    neighbourCount++;
                }
                if (*cell[i + x][j] == 1) { //Checks middle row
                    neighbourCount++;
                }
                if (*cell[i + x][j + 1] == 1) { //Checks bottom row
                    neighbourCount++;
                }
            }
        }
    }
    else if (i == GRIDSIZEX - 1) {
        //Right corner check
        if (j == 0) { //Top right corner
            if ((*cell[i - 1][GRIDSIZEY - 1] == 1) || (*cell[i][GRIDSIZEY - 1] == 1) || (*cell[0][GRIDSIZEY - 1] == 1)) { //Top row
                neighbourCount++;
            }
            if ((*cell[i - 1][j] == 1) || (*cell[i][j] == 1) || (*cell[0][j] == 1)) { //Middle row
                neighbourCount++;
            }
            if ((*cell[i - 1][j + 1] == 1) || (*cell[i][j + 1] == 1) || (*cell[0][j + 1] == 1)) { //Bottom row
                neighbourCount++;
            }
        }
        else if (j == GRIDSIZEY - 1) { //Bottom right corner
            if ((*cell[i - 1][j - 1] == 1) || (*cell[i][j - 1] == 1) || (*cell[0][j - 1] == 1)) { //Top row
                neighbourCount++;
            }
            if ((*cell[i - 1][j] == 1) || (*cell[i][j] == 1) || (*cell[0][j] == 1)) { //Middle row
                neighbourCount++;
            }
            if ((*cell[i - 1][0] == 1) || (*cell[i][0] == 1) || (*cell[0][0] == 1)) { //Bottom row
                neighbourCount++;
            }
        }
        else { //Check along the bottom x border
            for (int x = -1; x < 2; x++) {
                if (*cell[i + x][j - 1] == 1) { //Checks top row
                    neighbourCount++;
                }
                if (*cell[i + x][j] == 1) { //Checks middle row
                    neighbourCount++;
                }
                if (*cell[i + x][0] == 1) { //Checks bottom row - connected to top border
                    neighbourCount++;
                }
            }
        }
    }
    if (j == 0 && i > 0 && i < GRIDSIZEX - 1) { //Check along the Left column
        for (int y = -1; y < 2; y++) {
            if (*cell[GRIDSIZEX - 1][j + y] == 1) { //Checks first column - connected to right border
                neighbourCount++;
            }
            if (*cell[i][j + y] == 1) { //Checks middle column
                neighbourCount++;
            }
            if (*cell[i + 1][j + y] == 1) { //Checks last column
                neighbourCount++;
            }
        }
    }
    else if (j == 0 && i > 0 && i < GRIDSIZEX - 1) { //Check along the Right column
        for (int y = -1; y < 2; y++) {
            if (*cell[i - 1][j + y] == 1) { //Checks first column - connected to right border
                neighbourCount++;
            }
            if (*cell[i][j + y] == 1) { //Checks middle column
                neighbourCount++;
            }
            if (*cell[0][j + y] == 1) { //Checks last column
                neighbourCount++;
            }
        }
    }
    if (*cell[i][j] == 1 ) {
        return neighbourCount - 1; //Don't count the middle cell
    }
    return neighbourCount;
}

//Set the cell value according to the rules
void set_cell(int i,int j, int ***cell,int ***iteratedCell,int neighbours) {
    if ((neighbours == 2 || neighbours == 3) && *cell[i][j] == 1) { //Any live cell with two or three live neighbours survives
        (*iteratedCell)[i][j] = 1; //Set the cell state for the iteration
    }
    if (neighbours == 3 && *cell[i][j] == 0) { //Any dead cell with three live neighbours becomes a live cell
        (*iteratedCell)[i][j] = 1;
    }
    //Default cell state is dead so no need to set them in the iterated grid
}

//Calculate the next step of the grid
void iterate_grid(int ***cell, int ***iteratedCell) {
    if (!PAUSE) { //As long as not paused
        for (int i = 0; i < GRIDSIZEX - 1; i++) {
            for (int j = 0; j < GRIDSIZEY - 1; j++) { //Calculate every cell
                if ((i > 0 && i < GRIDSIZEX - 1) && (j > 0 && j < GRIDSIZEY - 1)) { //Avoid edge cases they require different calculation
                    set_cell(i, j, cell, iteratedCell, check_neighbours(i,j, cell)); //Set cell state
                }
                else { //Check edge borders
                    set_cell(i, j, cell, iteratedCell, edge_check_neighbours(i, j, cell)); //Set cell state
                }
            }
        }
    }
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
    PAUSE = false; //Initial state is not paused
    G.sizeX = G1.sizeX = (GRIDSIZEX - 1); //Grid X size starting from 0
    G.sizeY = G1.sizeY = (GRIDSIZEY - 1); //Grid Y size starting from 0
    initialise_grid(&G.cell, G.sizeX, G.sizeY);
    initialise_grid(&G1.cell, G1.sizeX, G1.sizeY);
    initialise_display(&G.cell);
    //cleanup_memory(); //Cleanup allocated memory after display exited
}

//Setup static environment
void initialise_static_environment() {
    G.sizeX = G1.sizeX = GRIDSIZEX - 1; //Grid X size
    G.sizeY = G1.sizeY = GRIDSIZEY - 1; //Grid Y size
    initialise_grid(&G.cell,G.sizeX, G.sizeY);
    initialise_display(&G.cell);
}