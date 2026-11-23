#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pigpio.h>
#define PIN 17

//int saveFile(char occupants[], int size);
int RemovePerson(char name, char *occupants, int size);
int getCurrentCount(char *occupants, int size);
int AddPerson(char name, char *occupants, int size);
void roomCheck(char *occupants, int size);

int AddPerson(char name, char *occupants, int size)
{
    for(int i=0; i< size; i++)
        {
            if(occupants[i]== '\0')
            {
                occupants[i]= name;
                printf("%c has been added.\n", name);
                return 0;
            }
        }
    printf("Room is full\n");
    return 1;
}
//remove an occupant from occupants array
int RemovePerson(char name, char *occupants, int size)
{
    if(occupants== NULL)
    {
        printf("Occupants array is not initialized.\n");
        return 1;
    }
    for(int i=0; i< size; i++)
        {
             if(occupants[i]== name)
            {
                occupants[i]= '\0';
                printf("%c has been removed.\n", name);
                return 0;
            }
        }
    if(getCurrentCount(occupants, size)== 0){printf("Cannot remove anyone the study room is empty.\n")}
    else{printf("%c was not found.\n", name);}
    return 1;
}
//returns current count of occupants in the study room
int getCurrentCount(char *occupants, int size) 
{
    int count = 0;
    for (int i = 0; i < size; i++) 
    {
        if (occupants[i] != '\0')  count++; //none null so we add it to our count
    }
    return count;
}
void roomCheck(char *occupants, int size)
{
    int finalcount= getCurrentCount(occupants, size);
    if(finalcount== size)
    {
        gpioWrite(PIN, 1);
        printf("ROOM FULL\n");
    }else{
         gpioWrite(PIN, 0);\
        printf("SPACE AVALIBLE\n);
    }
}

int main(int arg, char* argv[]) 
{
    gpioInitialise();
    gpioSetMode(PIN, PI_OUTPUT);
    
    int Size= 7;
    char *Occupants= calloc(Size, sizeof(char));
    if(Occupants== NULL)
    {
        printf("Memory allocation failed.\n");
        gpioTerminate();
        return 1;
    }
    File *file;
    file= fopen("Occupancy.txt", "w+");
    if(file== NULL)
    {
        printf("File failed to open.\n");
        return 1;
    }
    int choice;
    int Running= 1;
    while(Running== 1)
    {
        printf("1. Add a person\n 2. Current room status\n 3. Change max capacity\n 4. Remove a person\n 0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
    switch(choice)
        {
            case 1:
                {
                    printf("Who is added? ");
                    char name;
                    scanf(" %c", &name);
                    AddPerson(name, Occupants, Size);
                    fprintf(file, "Person %c was added.\n", name);
                    roomCheck(Occupants, Size);
                }break;
            case 2:
                {
                    printf("Avalible space\n");
                    printf("%d/%d", getCurrentCount(Occupants, Size), Size);
                    fprintf(file, "Capacity was checked.\n");
                    roomCheck(Occupants, Size);
                }break;
            case 3:
                {
                    printf("What is the new size? ");
                    int newSize;
                    scanf("%d", &newSize);
                    char *instance= realloc(Occupants, newSize*sizeof(char));
                     if(instance== NULL)
                    {
                        printf("Memory allocation failed.\n");
                        break;
                    }
                    Occupants= instance;
                    Size= newSize;
                    printf("Size changed to &d", Size);
                    fprintf(file, "Max capacity was changed to &d\n", newSize);
                    roomCheck(Occupants, Size);
                }break;
            case 4:
                {
                    printf("Who is leaving? "):
                    char name;
                    scanf("%c", name);
                    RemovePerson(name, Occupants, Size);
                    fprintf(file, "%c was removed.\n", name);
                    roomCheck(Occupants, Size);
                }break;
            case 0:
                {
                    fprintf(file, "Exited the Program.\n");
                    Running=0;
                }break;
            default:
            printf("Invalid choice");
            break;
        }
    }

    free(Occupants);
    gpioWrite(PIN, 0);
    gpioTerminate();
    fclose(file);
    return 0;
}

/*int saveFile(char occupants[], int size) {
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

}*/





