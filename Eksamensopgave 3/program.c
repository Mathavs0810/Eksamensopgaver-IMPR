/*
Navn: Mathias Øhlenschlæger Storgaard
Email: mstorg24@student.aau.dk
Fag: IMPR
Studieretning: Software
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KAMPE 90
#define HOLD 12

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

int pointFordeling(int hold1Maal, int hold2Maal);
void filIndlaesning(kampInfo *infoArray);
void holdIndlaesning(kampInfo *infoArray, hold *holdArray);
void fordel_hold_data(kampInfo *infoArray, hold *holdArray);
int compare(const void* a, const void* b);


int main(void){
    kampInfo infoArray[KAMPE]; 
    hold holdArray[HOLD]; 

    filIndlaesning(infoArray); //Filindlæsning til kampInfo struct
    holdIndlaesning(infoArray, holdArray); // Indsætning af hold i hold struct.
    fordel_hold_data(infoArray, holdArray); //Gennemgår alt kampInfo og indsættes i hold struct. 

    qsort(holdArray, 12, sizeof(hold), compare); // Sortere pts således at scoreboardet, går fra bedst til værst.
    
    //Print af scoreboard
    printf("Team  Pts  GS   GA \n"); // GS = Goals Scored, GA = Goals Against
    printf("------------------\n");
    for(int i = 0; i < HOLD; i++){
        printf("%-5s %-4d %-4d %d\n", holdArray[i].holdnavn, holdArray[i].point, holdArray[i].goals_scored, holdArray[i].goals_against);
    }

    return 0;
}


void filIndlaesning(kampInfo *infoArray){ 
    FILE *file = fopen("kampe-2024-2025.txt", "r");
    if (file == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < KAMPE; i++){
        if(fscanf(file, "%s %s %s %s - %s %d - %d %d", infoArray[i].weekday, infoArray[i].date, infoArray[i].clock, infoArray[i].hold1, infoArray[i].hold2, &infoArray[i].hold1maal, &infoArray[i].hold2maal, &infoArray[i].tilskuertal) != 8){
            printf("Fejl");
        }
    }
    fclose(file);
}

void holdIndlaesning(kampInfo *infoArray, hold *holdArray){
    char *holdnavne[] = {"AGF", "FCM", "BIF", "FCK", "LBK", "AaB", "FCN", "SIF", "VFF", "RFC", "SJF", "VB"};
    // Hold indlæsning
    for(int i = 0; i < HOLD; i++){
        strcpy(holdArray[i].holdnavn, holdnavne[i]);
        holdArray[i].point = 0;
        holdArray[i].goals_scored = 0;
        holdArray[i].goals_against = 0;
    }
} // Initialisering af hold i array, og værdier sættes til 0.

int pointFordeling(int hold1Maal, int hold2Maal){
    if(hold1Maal > hold2Maal){
        return 3;
    } else if (hold1Maal == hold2Maal){
        return 1; 
    } else {
        return 0;
    }
} // Fordeling af point, hvis de vinder, uafgjort eller taber.

void fordel_hold_data(kampInfo *infoArray, hold *holdArray){
    for(int i = 0; i < KAMPE; i++){
        for(int j = 0; j < HOLD; j++){
            if(strcmp(holdArray[j].holdnavn, infoArray[i].hold1) == 0){
                holdArray[j].point += pointFordeling(infoArray[i].hold1maal, infoArray[i].hold2maal);
                holdArray[j].goals_against += infoArray[i].hold2maal;
                holdArray[j].goals_scored += infoArray[i].hold1maal;
            } else if(strcmp(holdArray[j].holdnavn, infoArray[i].hold2) == 0){
                holdArray[j].point += pointFordeling(infoArray[i].hold2maal, infoArray[i].hold1maal);
                holdArray[j].goals_against += infoArray[i].hold1maal;
                holdArray[j].goals_scored += infoArray[i].hold2maal;
            }
        }
    }// To for loops der køre, som tjekker hver kamp og fordeler point, goals scored og goals against til de respektive hold.
} // Hvis holdnavn i hold struct er det samme som hold1 i kampInfo struct, så tilføjes point, goals scored og goals against til det hold.

int compare(const void* a, const void* b) {
    hold *teamA = (hold *)a;
    hold *teamB = (hold *)b;

    if (teamB->point != teamA->point) {
        return teamB->point - teamA->point;
    }

    int goal_diffA = teamA->goals_scored - teamA->goals_against;
    int goal_diffB = teamB->goals_scored - teamB->goals_against;
    return goal_diffB - goal_diffA;
} // Sammenligner holdene, således at holdene med flest point og bedst mål difference kommer først.

