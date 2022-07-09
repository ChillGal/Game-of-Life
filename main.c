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
    char pauseBool[6], charInfinite[12];
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
                printf("Which setting do you want to change?\n"); //Printf split for readability
                printf("%-3s %-10s\n", "1.", "Grid Size");
                printf("%-3s %-10s\n", "2.", "Initial State");
                printf("%-3s %-10s\n", "3.", "File Location");
                printf("%-3s %-10s\n", "4.", "Iteration Speed");
                printf("%-3s %-10s\n", "5.", "Reset to default");
                printf("%-3s %-10s\n", "6.", "Save settings");
                printf("%-3s %-10s\n", "7.", "Load settings");
                printf("%-3s %-10s\n", "8.", "List settings");
                printf("%-3s %-10s\n", "9.", "Save game");
                printf("%-3s %-10s\n", "10.", "Load game");
                printf("%-3s %-10s\n", "11.", "Grid border");
                printf("%-3s %-10s\n", "0.", "Back");
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
                        maxX = GRIDSIZEX - 1;
                        maxY = GRIDSIZEY -1;
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
                            strcpy(pauseBool, "False");
                        }
                        else {
                            strcpy(pauseBool, "True");
                        }
                        if (infinite == 0) {
                            strcpy(charInfinite, "Infinite");
                        }
                        else {
                            strcpy(charInfinite, "Restricted");
                        }
                        printf("Current settings\n");
                        printf("%-15s | %-10s\n", "Setting", "Value");
                        printf("%-15s | %-10d\n", "Width", GRIDSIZEX);
                        printf("%-15s | %-10d\n", "Height", GRIDSIZEY);
                        printf("%-15s | %-10d\n", "Iteration time", ITERATETIME);
                        printf("%-15s | %-10s\n", "Pause state", pauseBool);
                        printf("%-15s | %-10s\n", "Grid border", charInfinite);
                        break;
                    case 9: //Save game
                        save_game();
                        break;
                    case 10: //Load game
                    load_game();
                        break;
                    case 11: //Toggle infinity grid
                        printf("Current grid border setting is: ");
                        if (infinite == 1) {
                            printf("Infinite\n");
                        }
                        else if (infinite == 0) {
                            printf("Restricted\n");
                        }
                        printf("Do you want to change the grid border? y/n\n");
                        fflush(stdin);
                        answer = malloc(sizeof (char) * 5);
                        fgets(answer,sizeof response, stdin); //Get input
                        if (strcmp(answer, "n\n") == 0 || strcmp(answer,"y\n") == 0) {
                            if (strcmp(answer, "n\n") == 0) {
                                printf("Grid border not changed. \n");
                                free(answer);
                                return 0;
                            }
                            printf("Grid border changed\n");
                            if (infinite == 0){
                                infinite = 1;
                            }
                            else if (infinite == 1) {
                                infinite = 0;
                            }
                        }
                        else {
                            printf("Invalid response. \n");
                            free(answer);
                        }
                        break;
                    default:
                        printf("Not a valid option. \n");
                }
                break;
            case 3: //Quit
                quit = true;
                cleanup_memory(); //Cleanup allocated memory after display exited
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
