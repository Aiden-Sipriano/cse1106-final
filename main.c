#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int saveFile(char occupants[], int size);
int removePerson(char name, char occupants[], int size);
int getCurrentCount(char occupants[], int size);

int main() {
    char occupants[] = {'A', 'B'};
    int size = sizeof(occupants) / sizeof(occupants[0]); //gets size of array for looping 
    printf(" %d\n", size);
    removePerson('A', occupants, size);
    removePerson('B', occupants, size);
    removePerson('K', occupants, size);

    printf(" %d\n", getCurrentCount(occupants, size));
    saveFile(occupants, size);


}

int saveFile(char occupants[], int size) {
    FILE *file;

    //Opens the file in write mode
    file = fopen("Occupancy.txt", "w");

    //Checks if the file is null
    if (file == NULL) {
        printf("File failed to open\n");
        return 1;
    }

    //Write to the file
    
    fprintf(file, "%d", getCurrentCount(occupants, size));

    //Close the file and save changes
    fclose(file);

}

//remove an occupant from occupants array
int removePerson(char name, char occupants[], int size) {
    
    for (int i = 0; i < size; i++) {
        if (occupants[i] != NULL && occupants[i] == name) {
            occupants[i] = '\0';
            return 0; //we found the name and set it to null
        } 
    }
    if (getCurrentCount(occupants, size) == 0) printf("Cannot remove anyone the study room is empty\n");
    else printf("%c was not found\n", name);
    return 1;
}

//returns current count of occupants in the study room
int getCurrentCount(char occupants[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (occupants[i] != NULL)  count++; //none null so we add it to our count
    }
    return count;
}
