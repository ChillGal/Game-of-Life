#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include "engine.h"
#include "display.h"

//Global Variables
int GRIDSIZEX = 160; //Grid X size
int GRIDSIZEY = 90; //Grid Y size
int maxX = 159;
int maxY = 89;
int ITERATETIME = 10; //Time between iterations in ms
bool PAUSE = false; //Pause state
struct grid G; //Main grid
struct grid G1; //Next step grid

//Create grid using 2D array using pointers
int initialise_grid(int ***cell, int SizeX, int SizeY) {
    *cell = (int **)malloc(sizeof(int *) * SizeX); //Allocate memory to vertical columns
    if ((*cell) == NULL) { //Check that memory has been allocated
        printf("Error occurred allocating memory to vertical columns.\n");
        return 1;
    }
    for (int i = 0; i < SizeX; i++) {
        (*cell)[i] = (int *)malloc(sizeof(int) * SizeY); //Allocate memory to horizontal rows
        if ((*cell)[i] == NULL){
            free(cell);
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
            if ((*cell)[i + x][j + y] == 1) {
                neighbourCount++;
            }
        }
    }
    if ((*cell)[i][j] == 1) {
        return neighbourCount - 1; //Don't count the middle cell
    }
    return neighbourCount;
}

//Check the edges of the grid with toroidal shape (donut shape)
int edge_check_neighbours(int i, int j, int ***cell) {
    int neighbourCount = 0;
    //Corner checks
    if (i == 0 && j == 0) { //Top left corner
        if ((*cell)[maxX][maxY] == 1) { //Top left
            neighbourCount++;
        }
        if ((*cell)[0][maxY] == 1) { //Top middle
            neighbourCount++;
        }
        if ((*cell)[1][maxY]) { //Top right
            neighbourCount++;
        }
        if ((*cell)[maxX][0] == 1) { //Middle left
            neighbourCount++;
        }
        if ((*cell)[0][0] == 1) { //Middle middle
            neighbourCount++;
        }
        if ((*cell)[1][0] == 1) { //Middle middle
            neighbourCount++;
        }
        if ((*cell)[maxX][1] == 1) { //Bottom left
            neighbourCount++;
        }
        if ((*cell)[0][1] == 1) { //Bottom middle
            neighbourCount++;
        }
        if ((*cell)[1][1] == 1) { //Bottom right
            neighbourCount++;
        }
    }
    else if (i == 0 && j == maxY) { //Bottom left
        if ((*cell)[maxX][maxY - 1] == 1) { //Top left
            neighbourCount++;
        }
        if ((*cell)[0][maxY - 1] == 1) { //Top middle
            neighbourCount++;
        }
        if ((*cell)[1][maxY - 1] == 1) { //Top right
            neighbourCount++;
        }
        if ((*cell)[0][maxY] == 1) { //Middle left
            neighbourCount++;
        }
        if ((*cell)[0][maxY] == 1) { //Middle middle
            neighbourCount++;
        }
        if ((*cell)[1][maxY] == 1) { //Middle right
            neighbourCount++;
        }
        if ((*cell)[maxX][0] == 1) { //Bottom left
            neighbourCount++;
        }
        if ((*cell)[0][0] == 1) { //Bottom middle
            neighbourCount++;
        }
        if ((*cell)[1][0] == 1) { //Bottom right
            neighbourCount++;
        }
    }
    else if (i == maxX && j == 0) { //Top right
        if ((*cell)[maxX - 1][maxY] == 1) { //Top left
            neighbourCount++;
        }
        if ((*cell)[maxX][maxY] == 1) { //Top middle
            neighbourCount++;
        }
        if ((*cell)[0][maxY] == 1) { //Top right
            neighbourCount++;
        }
        if ((*cell)[maxX - 1][0] == 1) { //Middle left
            neighbourCount++;
        }
        if ((*cell)[maxX][0] == 1) { //Middle middle
            neighbourCount++;
        }
        if ((*cell)[0][0] == 1) { //Middle right
            neighbourCount++;
        }
        if ((*cell)[maxX - 1][1] == 1) { //Bottom left
            neighbourCount++;
        }
        if ((*cell)[maxX][1] == 1) { //Bottom middle
            neighbourCount++;
        }
        if ((*cell)[0][1] == 1) { //Bottom right
            neighbourCount++;
        }
    }
    else if (i == maxX && j == maxY) { //Bottom right
        if ((*cell)[maxX - 1][maxY - 1] == 1) { //Top left
            neighbourCount++;
        }
        if ((*cell)[maxX][maxY - 1] == 1) { //Top middle
            neighbourCount++;
        }
        if ((*cell)[0][maxY - 1] == 1) { //Top right
            neighbourCount++;
        }
        if ((*cell)[maxX - 1][maxY] == 1) { //Middle left
            neighbourCount++;
        }
        if ((*cell)[maxX][maxY] == 1) { //Middle middle
            neighbourCount++;
        }
        if ((*cell)[0][maxY] == 1) { //Middle right
            neighbourCount++;
        }
        if ((*cell)[maxX - 1][0] == 1) { //Bottom left
            neighbourCount++;
        }
        if ((*cell)[maxX][0] == 1) { //Bottom middle
            neighbourCount++;
        }
        if ((*cell)[0][0] == 1) { //Bottom right
            neighbourCount++;
        }
    }
    //Border checks
    if (i > 0 && i < maxX && j == 0) { //Top row
        for (int x = -1;x < 2; x++) {
            if ((*cell)[i + x][maxY] == 1) { //Top row
                neighbourCount++;
            }
            if ((*cell)[i + x][j] == 1) { //Middle row
                neighbourCount++;
            }
            if((*cell)[i + x][j + 1] == 1) { //Bottom row
                neighbourCount++;
            }
        }
    }
    else if (i > 0 && i < maxX && j == maxY) { //Bottom row
        for (int x = -1;x < 2; x++) {
            if ((*cell)[i + x][j - 1] == 1) { //Top row
                neighbourCount++;
            }
            if ((*cell)[i + x][j] == 1) { //Middle row
                neighbourCount++;
            }
            if ((*cell)[i + x][0] == 1) { //Bottom row
                neighbourCount++;
            }
        }
    }
    else if (i == 0 && j > 0 && j < maxY) { //Left column
        for (int y = -1; y < 2; y++) {
            if ((*cell)[maxX][j + y] == 1) { //Left column
                neighbourCount++;
            }
            if ((*cell)[i][j + y] == 1) { //Middle column
                neighbourCount++;
            }
            if ((*cell)[i + 1][j + y] == 1) { //Right column
                neighbourCount++;
            }
        }
    }
    else if (i == maxX && j > 0 && j < maxY) { //Right column
        for (int y = -1; y < 2; y ++) {
            if ((*cell)[i - 1][j + y] == 1) { //Left column
                neighbourCount++;
            }
            if ((*cell)[i][j + y] == 1) { //Middle column
                neighbourCount++;
            }
            if ((*cell)[0][j + y] == 1) { //Right column
                neighbourCount++;
            }
        }
    }
    if ((*cell)[i][j] == 1 ) {
        return neighbourCount - 1; //Don't count the middle cell
    }
    return neighbourCount;
}

//Set the cell value according to the rules
void set_cell(int i,int j, int ***cell, int ***iteratedCell, int neighbours) {
    if ((neighbours == 2 || neighbours == 3) && (*cell)[i][j] == 1) { //Any live cell with two or three live neighbours survives
        (*iteratedCell)[i][j] = 1; //Set the cell state for the iteration
    }
    else if (neighbours == 3 && (*cell)[i][j] == 0) { //Any dead cell with three live neighbours becomes a live cell
        (*iteratedCell)[i][j] = 1;
    }
    else {(*iteratedCell)[i][j] = 0;}
    //Default cell state is dead so no need to set them in the iterated grid
}

//Calculate the next step of the grid
void iterate_grid(int ***cell, int ***iteratedCell) {
    if (!PAUSE) { //As long as not paused
        for (int i = 0; i < GRIDSIZEX; i++) {
            for (int j = 0; j < GRIDSIZEY; j++) { //Calculate every cell
                if ((i > 0 && i < GRIDSIZEX - 1) && (j > 0 && j < GRIDSIZEY - 1)) { //Avoid edge cases they require different calculation
                    set_cell(i, j, cell, iteratedCell, check_neighbours(i, j, cell)); //Set cell state
                }
                else { //Check edge borders
                    set_cell(i, j, cell, iteratedCell, edge_check_neighbours(i, j, cell)); //Set cell state
                }
            }
        }
        //Overwrite old grid values
        for (int i = 0; i < GRIDSIZEX; i++) {
            for (int j = 0; j < GRIDSIZEY; j++) {
                if ((G.cell)[i][j] != (G1.cell)[i][j]) {
                    (G.cell)[i][j] = (G1.cell)[i][j];
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
    G.sizeX = G1.sizeX = GRIDSIZEX; //Grid X size starting from 0
    G.sizeY = G1.sizeY = GRIDSIZEY; //Grid Y size starting from 0
    maxX = GRIDSIZEX - 1;
    maxY = GRIDSIZEY - 1;
    initialise_grid(&G.cell, G.sizeX, G.sizeY);
    initialise_grid(&G1.cell, G1.sizeX, G1.sizeY);
    initialise_display(&G.cell);
    //cleanup_memory(); //Cleanup allocated memory after display exited
}

//Setup static environment
void initialise_static_environment() {
    G.sizeX = G1.sizeX = GRIDSIZEX; //Grid X size
    G.sizeY = G1.sizeY = GRIDSIZEY; //Grid Y size
    maxX = GRIDSIZEX - 1;
    maxY = GRIDSIZEY - 1;
    initialise_grid(&G.cell,G.sizeX, G.sizeY);
    initialise_display(&G.cell);
}