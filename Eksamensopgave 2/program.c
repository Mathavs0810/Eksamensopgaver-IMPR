#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int *roll_multiple_dice(int nTerninger);

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
} // Anvendes til qsort

void ones(int array[], int nTerninger, int resultsArray[]){
    int sum = 0; 
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 1){
            sum++;
        } 
    }
    resultsArray[0] = sum * 1;
}


void twos(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 2){
            sum++;
        } 
    }
    resultsArray[1] = sum * 2;
}

void threes(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 3){
            sum++;
        } 
    }
    resultsArray[2] = sum * 3;
}
void fours(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 4){
            sum++;
        } 
    }
    resultsArray[3] = sum * 4;
}
void fives(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 5){
            sum++;
        } 
    }
    resultsArray[4] = sum * 5;
}

void sixes(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 6){
            sum++;
        } 
    }
    resultsArray[5] = sum * 6;
}

void bonus(int resultsArray[]){
    int bonus = 0;
    bonus = resultsArray[0] + resultsArray[1] + resultsArray[2] + resultsArray[3] + resultsArray[4] + resultsArray[5];
    if(bonus >= 63){
        resultsArray[6] = 50;
    } else {
        resultsArray[6] = 0;
    }
}

void onePair(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1]){
        sum = array[i] * 2;
        resultsArray[7] = sum;
        break;
       } 
    }
}

void twoPair(int array[], int nTerninger, int resultsArray[]){
    int sum1 = 0;
    int sum2 = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1]){
        if(sum1 == 0){
            sum1 = array[i] * 2;
            i--;
        } else if(sum2 == 0 && array[i] != array[i+1]){
            sum2 = array[i] * 2;
            resultsArray[8] = sum1 + sum2;
            break;
            }
        }
    } 
}
void threeOfAKind(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1] && array[i] == array[i-2]){
        sum = array[i] + array[i-1] + array[i-2];
        resultsArray[9] = sum;
        break;
       } 
    }
}

void fourOfAKind(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1] && array[i] == array[i-2] && array[i] == array[i-3]){
        sum = array[i] + array[i-1] + array[i-2] + array[i-3];
        resultsArray[10] = sum;
        break;
       } 
    }
}

void small(int array[], int nTerninger, int resultsArray[]){
    int target = 1;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == target){
            target++;
        }
        if(target == 6){
            resultsArray[11] = 15;
            break;
        }
    }
}

void large(int array[], int nTerninger, int resultsArray[]){
    int target = 2;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == target){
            target++;
        }
        if(target == 7){
            resultsArray[12] = 20;
            break;
        }
    }
}

void fullHouse(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    int sum1 = 0;
    int i = 0; 
    int j = 0; 
    
    for(i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1] && array[i] == array[i-2]){
        sum = array[i] * 3;
        break; 
     }
    }
    for(j = nTerninger-1 ; j >= 1; j--){
        if(array[j] == array[j-1]){
            if(array[i] != array[j]){
                sum1 = array[j] * 2;
                break;
            }
            }
        } 
        if(sum > 0 && sum1 > 0){
            resultsArray[13] = sum + sum1;
        }
}

void chance(int array[], int nTerninger, int resultsArray[]){
    int sum = 0;
    for(int i = nTerninger - 1; i >= nTerninger - 5; i--){
        sum += array[i];
    }
    resultsArray[14] = sum;
}

void yatzy(int array[], int nTerninger, int resultsArray[]){ 
    int sum = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1] && array[i] == array[i-2] && array[i] == array[i-3] && array[i] == array[i-4]){
        sum = 50;
        resultsArray[15] = sum;
        break;
       } 
    }
}

int *roll_multiple_dice(int nTerninger){
    srand(time(NULL));
    int *array = (int*) malloc(nTerninger * sizeof(int));
    for (int i = 0; i < nTerninger; i++){
        array[i] = (rand() % 6 + 1);
    }
    qsort(array, nTerninger, sizeof(int), compare);
    return array;
}

void save_array(int array[], int nTerninger, int (*diceArrays)[nTerninger], int index){
    for(int i = 0; i < nTerninger; i++){
        diceArrays[index][i] = array[i];
    }
}

void run_game(){
    int nTerninger;
    int *array;
    int resultsArray[16] = {0}; 
    const char *combinations[] = {
    "Ones",
    "Twos",
    "Threes",
    "Fours",
    "Fives",
    "Sixes",
    "Bonus",
    "One Pair",
    "Two Pair",
    "Three of a kind",
    "Four of a kind",
    "Small Straight",
    "Large Straight",
    "Full House",
    "Chance",
    "Yatzy",
    };    

    printf("Indtast hvor mange terninger du vil kaste?\n");
    scanf("%d", &nTerninger);
    if(nTerninger < 5){
        exit(EXIT_FAILURE);
    }
    int diceArrays[16][nTerninger];

   // 1-6 
    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 0);
    ones(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 1);
    twos(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 2);
    threes(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 3);
    fours(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 4);
    fives(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 5);
    sixes(array, nTerninger, resultsArray);

    bonus(resultsArray);
    array = memset(array, 0, sizeof(int) * nTerninger);
    save_array(array, nTerninger, diceArrays, 6);

    // Par 1 til FourOfAKind
    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 7);
    onePair(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 8);
    twoPair(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 9);
    threeOfAKind(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 10);
    fourOfAKind(array, nTerninger, resultsArray);
    // resten
    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 11);
    small(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 12);
    large(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 13);
    fullHouse(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 14);
    chance(array, nTerninger, resultsArray);

    array = roll_multiple_dice(nTerninger);
    save_array(array, nTerninger, diceArrays, 15);
    yatzy(array, nTerninger, resultsArray);

    for(int i = 0; i < 16; i++){
        printf("%s: %d \n", combinations[i], resultsArray[i]);
        printf("Dies: ");
        for(int j = 0; j < nTerninger; j++){
            printf("%d ", diceArrays[i][j]);
        }
        printf("\n");
    }
}

int main(void){
    int answer = 1;
    while(answer != 0){
        run_game();
        printf("Do you wanna play again? (y = 1/n = 0)\n");
        scanf(" %d", &answer);
    }   
    return 0;
}

