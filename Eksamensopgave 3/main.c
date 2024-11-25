#include <stdio.h>
#include <stdlib.h>

#define KAMPE 90

int main(void){
    typedef struct kampInfo {
        char weekday[10];
        char date[10];
        char clock[10];
        char hold1[10];
        char hold2[10];
        int hold1maal;
        int hold2maal;
        int tilskuertal;
    } kampInfo;
    typedef struct hold {
        char holdnavn[30];
        int point;
        int goals_scored;
        int goals_against;

    } hold;
    kampInfo infoArray[90];
    hold holdArray[12];

    // Filindlæsning 
    FILE *file = fopen("kampe-2024-2025.txt", "r");
    if (file == NULL) {
       printf("Error opening file");
       return 1;
    }
    for(int i = 0; i < KAMPE; i++){
        if(fscanf(file, "%s %s %s %s - %s %d - %d %d", infoArray[i].weekday, infoArray[i].date, infoArray[i].clock, infoArray[i].hold1, infoArray[i].hold2, &infoArray[i].hold1maal, &infoArray[i].hold2maal, &infoArray[i].tilskuertal) != 8){
            printf("Fejl");
        }
    }

    // Hold indlæsning
    




    fclose(file);

    return 0;
}