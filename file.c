#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "file.h"


FILE *fptr;
int NEWGRIDSIZEX, NEWGRIDSIZEY, NEWITERATETIME, NEWINFINITE;
bool NEWPAUSE;

int check_file_exists(char *fileName, int readType) {
    if (readType == 0) {
        fptr = fopen(fileName, "r");
    }
    else if (readType == 1) {
        fptr = fopen(fileName, "rb");
    }
    else {
        return 1;
    }
    if (fptr == NULL) {
        return 1;
    }
    fclose(fptr);
    return 0;
}
//Write current parameters to file
void write_settings() {
    fprintf(fptr, "%d\n", GRIDSIZEX);
    fprintf(fptr, "%d\n", GRIDSIZEY);
    fprintf(fptr, "%d\n",ITERATETIME);
    fprintf(fptr, "%d\n", PAUSE);
    fprintf(fptr, "%d\n", infinite);
}

void read_settings() {
    char *inputString = NULL;
    inputString =(char *) malloc(sizeof(char) * 15);
    NEWGRIDSIZEX=strtol(fgets(inputString, 5, fptr), &inputString, 10);
    NEWGRIDSIZEY=strtol(fgets(inputString, 5, fptr), &inputString, 10);
    NEWITERATETIME=strtol(fgets(inputString, 5, fptr), &inputString, 10);
    NEWPAUSE=strtol(fgets(inputString, 5, fptr), &inputString, 10);
    NEWINFINITE=strtol(fgets(inputString, 5, fptr), &inputString, 10);
    inputString = NULL;
    free(inputString);
}

void write_game() {
    fwrite(G.cell,sizeof (G.cell),1,fptr);
}

void read_game() {

}
int save_settings() {
    char *fileName = "settings.ini"; //File name
    char *response= NULL; //Response pointer
    char pauseBool[6], newPauseBool[6];
    if (check_file_exists(fileName,0) == 1) {
        printf("Existing settings not found. Creating new file...\n");
        fptr = fopen(fileName, "w"); //Open file in write mode
        write_settings();
        fclose(fptr);
        return 0;
    }
    fptr = fopen(fileName,"r");
    read_settings();
    fclose(fptr);
    // Convert boolean to string
    if (PAUSE == 0){
        strcpy(pauseBool, "false");
    }
    else {
        strcpy(pauseBool, "true");
    }
    if (NEWPAUSE == 0) {
        strcpy(newPauseBool, "false");
    }
    else {
        strcpy(newPauseBool, "true");
    }
    printf("Existing settings found.\n");
    printf("%-15s | %-10s | %-10s\n", "Setting", "Saved", "New");
    printf("%-15s | %-10d | %-10d\n", "Width", NEWGRIDSIZEX, GRIDSIZEX);
    printf("%-15s | %-10d | %-10d\n", "Height", NEWGRIDSIZEY, GRIDSIZEY);
    printf("%-15s | %-10d | %-10d\n", "Iteration time", NEWITERATETIME, ITERATETIME);
    printf("%-15s | %-10s | %-10s\n", "Pause state", newPauseBool, pauseBool);
    printf("%-15s | %-10s | %-10s\n", "Border", infinite, NEWINFINITE); //TODO ADD CHECKS FOR INFINITE AND ADD TO LIST SETTINGS IN MENU
    printf("Do you want to overwrite the current settings? y/n\n");
    response = malloc(sizeof (char) * 5); //Allocate 5 char's worth of memory.
    fflush(stdin); //Clear input buffer
    fgets(response,sizeof response, stdin); //Get input
    if (strcmp(response, "n\n") == 0 || strcmp(response,"y\n") == 0){ //Check for valid input
        if (strcmp(response, "n\n") == 0) {
            printf("Settings not saved.\n");
            return 0;
        }
        free(response);
        printf("Overwriting existing settings.\n");
        fptr = fopen(fileName, "w+"); //Open file in write mode
        write_settings();
        fclose(fptr); //Close file
        return 0;
    }
    printf("Invalid response. \n");
    free(response); //Cleanup memory
    return 1;
}

int load_settings() {
    char *fileName = "settings.ini"; //File name
    char *response= NULL; //Response pointer
    char pauseBool[6], newPauseBool[6], charInfinite[12], charNewInfinite[12];
    if (check_file_exists(fileName,0) == 1) {
        printf("Settings file could not be loaded.\n");
        free(fileName);
        return 1;
    }
    fptr = fopen(fileName,"r");
    read_settings();
    fclose(fptr);
    free(fileName);
    // Convert boolean to string
    if (PAUSE == 0) {
        strcpy(pauseBool, "False");
    }
    else {
        strcpy(pauseBool, "True");
    }
    if (NEWPAUSE == 0) {
        strcpy(newPauseBool, "False");
    }
    else {
        strcpy(newPauseBool, "True");
    }
    if (infinite == 0) {
        strcpy(charInfinite, "Infinite");
    }
    else {
        strcpy(charInfinite, "Restricted");
    }
    if (NEWINFINITE == 0) {
        strcpy(charNewInfinite, "Infinite");
    }
    else {
        strcpy(charNewInfinite, "Restricted");
    }
    printf("Settings file found.\n");
    printf("%-15s | %-10s | %-10s\n", "Setting", "Current", "New");
    printf("%-15s | %-10d | %-10d\n", "Width", GRIDSIZEX, NEWGRIDSIZEX);
    printf("%-15s | %-10d | %-10d\n", "Height", GRIDSIZEY, NEWGRIDSIZEY);
    printf("%-15s | %-10d | %-10d\n", "Iteration time", ITERATETIME, NEWITERATETIME);
    printf("%-15s | %-10s | %-10s\n", "Pause state", pauseBool, newPauseBool);
    printf("%-15s | %-10s | %-10s\n", "Grid border", charInfinite, charNewInfinite);
    printf("Do you want to overwrite the current settings? y/n\n");
    free(pauseBool);
    free(newPauseBool);
    response = malloc(sizeof (char) * 5); //Allocate 5 char's worth of memory.
    fflush(stdin);
    fgets(response,sizeof response, stdin); //Get input
    if (strcmp(response, "n\n") == 0 || strcmp(response,"y\n") == 0){
        if (strcmp(response, "n\n") == 0) {
            printf("Settings file not loaded.\n");
            free(response);
            return 0;
        }
        //Overwrite the existing settings
        GRIDSIZEX = NEWGRIDSIZEX;
        GRIDSIZEY = NEWGRIDSIZEY;
        ITERATETIME = NEWITERATETIME;
        PAUSE = NEWPAUSE;
        infinite = NEWINFINITE;
        free(response);
        return 0;
    }
    printf("Invalid response. \n");
    free(response); //Cleanup memory
    return 1;
}

//TODO Save game state
int save_game() {
    char *fileName = "Save.bin"; //File name
    char *response= NULL; //Response pointer
    if (check_file_exists(fileName,1) == 1) {
        printf("Existing save not found. Creating new save...\n");
        fptr = fopen(fileName, "wb"); //Open file in write mode
        write_game();
        fclose(fptr);
        return 0;
    }
    printf("Existing game save found!\nDo you want to overwrite the current save? y/n\n");
    response = malloc(sizeof (char) * 5); //Allocate 5 char's worth of memory.
    fflush(stdin);
    fgets(response,sizeof response, stdin); //Get input
    if (strcmp(response, "n\n") == 0 || strcmp(response,"y\n") == 0){
        if (strcmp(response, "n\n") == 0) {
            printf("Save file not overwritten.\n");
            free(response);
            return 0;
        }
        //Overwrite the existing save
        fptr = fopen(fileName, "wb+"); //Open file in write mode
        write_game();
        free(response);
        return 0;
    }
    printf("Invalid response. \n");
    free(response); //Cleanup memory
    return 1;
}

//TODO Load game state
int load_game() {
    char *fileName = "Save.bin"; //File name
    char *response= NULL; //Response pointer
    if (check_file_exists(fileName,1) == 1) {
        printf("Save file could not be loaded.\n");
        free(fileName);
        return 1;
    }
    fptr = fopen(fileName,"rb");
    read_game();
    fclose(fptr);
    free(fileName);
    return -99;
}
