#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "engine.h"
#include "file.h"

/*
----Game Rules----
 * Any live cell with two or three live neighbours survives.
 * Any dead cell with three live neighbours becomes a live cell.
 * All other live cells die in the next generation. Similarly, all other dead cells stay dead.
 */

int menu() { //Main menu
    printf("Conway's game of life in C\n");
    char *answer;
    char pauseBool[6];
    int response;
    bool quit = false;
    //Menu loop
    do {
        answer = (char *) malloc(sizeof(char) * 3); //Allocate 3 chars of memory to pointer
        printf("Select an option\n1. Start\n2. Modify config\n3. Quit\n");
        fflush(stdin); //Clear input buffer
        response = atoi(fgets(answer, 3 * sizeof(char), stdin)); //Get int from input
        free(answer); //Release memory allocated to pointer
        switch(response) {
            case 1: //Start with default settings
                printf("Starting...\n");
                initialise_engine();
                printf("Finished.\n");
                break;
            case 2: //Change settings
                answer = (char *) malloc(sizeof(char) * 3);
                printf("Which setting do you want to change?\n1. Grid Size\n2. Initial State\n3. File Location\n4. Iteration Speed\n5. Reset to default\n6. Save settings\n7. Load settings\n8. List settings\n0. Back\n");
                fflush(stdin);
                response = atoi(fgets(answer, 3 * sizeof(char), stdin));
                free(answer);
                switch (response) {
                    case 0: //Go back
                        break;
                    case 1: //Change grid size
                        printf("Current grid is x = %d and y = %d. \n", GRIDSIZEX,GRIDSIZEY); //Display current grid size
                        printf("Enter new grid X size:"); //Get new X size
                        fflush(stdin);
                        scanf("%d", &GRIDSIZEX);
                        printf("Enter new grid Y size:"); //Get new Y size
                        fflush(stdin);
                        scanf("%d", &GRIDSIZEY);
                        printf("The new X size is : %d and the new Y size is : %d. \n\n", GRIDSIZEX, GRIDSIZEY); //Display new grid size
                        break;
                    case 2: //Change initial state
                        //TODO Call initial state function
                        printf("Loading static environment...");
                        initialise_static_environment();
                        break;
                    case 3: //Change file location
                        //TODO Call change file location function
                        break;
                    case 4: //Change iteration speed
                        printf("Current iteration speed = %d ms. \n", ITERATETIME); //Display iteration speed
                        printf("Enter new iteration time:");
                        fflush(stdin);
                        scanf("%d",&ITERATETIME);
                        printf("The new iteration speed = %d ms.\n",ITERATETIME);
                        break;
                    case 5: //Reset to default parameters
                        GRIDSIZEX = 160;
                        GRIDSIZEY = 90;
                        ITERATETIME = 10;
                        PAUSE = false;
                        printf("Parameters have been reset!\n");
                        break;
                    case 6: //Save current settings
                        save_settings();
                        break;
                    case 7: //Load settings from file
                        load_settings();
                        break;
                    case 8: //List current settings
                        if (PAUSE == 0) {
                            strcpy(pauseBool, "false");
                        }
                        else {
                            strcpy(pauseBool, "true");
                        }
                        printf("Current settings\n");
                        printf("%-15s | %-10s\n", "Setting", "Value");
                        printf("%-15s | %-10d\n", "Width", GRIDSIZEX);
                        printf("%-15s | %-10d\n", "Height", GRIDSIZEY);
                        printf("%-15s | %-10d\n", "Iteration time", ITERATETIME);
                        printf("%-15s | %-10s\n", "Pause state", pauseBool);
                        break;
                    default:
                        printf("Not a valid option. \n");
                }
                break;
            case 3: //Quit
                quit = true;
                break;
            default:
                printf("Not a valid option. \n");
        }
    }while(!quit);
    return 0;
}

int main() {
    menu();
    return 0;
}
