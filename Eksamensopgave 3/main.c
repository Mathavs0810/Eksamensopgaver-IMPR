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
void assign_team_data(kampInfo *infoArray, hold *holdArray);

int compare(const void* a, const void* b) {
    hold *teamA = (hold *)a;
    hold *teamB = (hold *)b;

    if (teamB->point != teamA->point) {
        return teamB->point - teamA->point;
    }
    
    int goal_diffA = teamA->goals_scored - teamA->goals_against;
    int goal_diffB = teamB->goals_scored - teamB->goals_against;
    return goal_diffB - goal_diffA;
}


int main(void){
    kampInfo infoArray[90];
    hold holdArray[12];
    filIndlaesning(infoArray);
    holdIndlaesning(infoArray, holdArray);
    assign_team_data(infoArray, holdArray);
    qsort(holdArray, 12, sizeof(hold), compare);
    
    for(int i = 0; i < HOLD; i++){
        printf("%s: Points: %d GS: %d GA: %d\n", holdArray[i].holdnavn, holdArray[i].point, holdArray[i].goals_scored, holdArray[i].goals_against);
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
}

int pointFordeling(int hold1Maal, int hold2Maal){
    if(hold1Maal > hold2Maal){
        return 3;
    } else if (hold1Maal == hold2Maal){
        return 1; 
    } else {
        return 0;
    }
}

void assign_team_data(kampInfo *infoArray, hold *holdArray){
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
    }
}

