#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int *roll_multiple_dice(int nTerninger);

struct Scoreboard{
    int ones;
    int twos;
    int threes;
    int fours;
    int fives;
    int sixes;
    int bonus;
    int onePair;
    int twoPair;
    int threeOfAKind;
    int fourOfAKind;
    int small;
    int large;
    int fullHouse; // Mangler et fiks
    int chance;
    int yatzy;
};

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
} // Anvendes til qsort

int ones(int array[], int nTerninger){
    int sum = -1;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 1){
            sum++;
        } 
    }
    if(sum >= 2){
        return sum * 1;
    } else {
        return 0;
    }
}

int twos(int array[], int nTerninger){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 2){
            sum++;
        } 
    }
    if(sum >= 2){
        return sum * 2;
    } else {
        return 0;
    }
}

int threes(int array[], int nTerninger){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 3){
            sum++;
        } 
    }
    if(sum >= 2){
        return sum * 3;
    } else {
        return 0;
    }
}
int fours(int array[], int nTerninger){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 4){
            sum++;
        } 
    }
    if(sum >= 2){
        return sum * 4;
    } else {
        return 0;
    }
}
int fives(int array[], int nTerninger){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 5){
            sum++;
        } 
    }
    if(sum >= 2){
        return sum * 5;
    } else {
        return 0;
    }
}

int sixes(int array[], int nTerninger){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == 6){
            sum++;
        } 
    }
    if(sum >= 2){
        return sum * 6;
    } else {
        return 0;
    }
}

int bonus(struct Scoreboard scoreboard){
    int bonus = 0;
    bonus = scoreboard.ones + scoreboard.twos + scoreboard.threes + scoreboard.fours + scoreboard.fives + scoreboard.sixes;
    if(bonus >= 63){
        return 50;
    } else {
        return 0;
    }
}

int onePair(int array[], int nTerninger){
    qsort(array,nTerninger, sizeof(int), compare);
    int sum = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1]){
        sum = array[i] + array[i-1];
        return sum;
       } 
        }
    return 0;
    }


int twoPair(int array[], int nTerninger){
    qsort(array, nTerninger, sizeof(int), compare);
    int sum1 = 0;
    int sum2 = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1]){
        if(sum1 == 0){
            sum1 = array[i] * 2;
            i--;
        } else if(sum2 == 0 && array[i] != array[i+1]){
            sum2 = array[i] * 2;
            return sum1 + sum2;
            }
        }
    }
    return 0;   
}
int threeOfAKind(int array[], int nTerninger){
    qsort(array, nTerninger, sizeof(int), compare);
    int sum = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1] && array[i] == array[i-2]){
        sum = array[i] + array[i-1] + array[i-2];
        return sum;
       } 
    }
    return 0;
}

int fourOfAKind(int array[], int nTerninger){
    qsort(array, nTerninger, sizeof(int), compare);
    int sum = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1] && array[i] == array[i-2] && array[i] == array[i-3]){
        sum = array[i] + array[i-1] + array[i-2] + array[i-3];
        return sum;
       } 
    }
    return 0;
}

int small(int array[], int nTerninger){
    qsort(array, nTerninger, sizeof(int), compare);
    int target = 1;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == target){
            target++;
        }
        if(target == 6){
            return 15;
        }
    }
    return 0;
}

int large(int array[], int nTerninger){
    qsort(array, nTerninger, sizeof(int), compare);
    int target = 2;
    for(int i = 0; i < nTerninger; i++){
        if(array[i] == target){
            target++;
        }
        if(target == 7){
            return 20;
        }
    }
    return 0;
}

int fullHouse(int array[], int nTerninger){
    qsort(array, nTerninger, sizeof(int), compare);
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
            return sum + sum1;
        }
        return 0; 
    }

int chance(int array[], int nTerninger){
    int sum = 0;
    for(int i = 0; i < nTerninger; i++){
        sum += array[i];
    }
    return sum;
}

int yatzy(int array[], int nTerninger){ 
    qsort(array, nTerninger, sizeof(int), compare);
    int sum = 0;
    for(int i = nTerninger - 1; i >= 1; i--){
       if(array[i] == array[i-1] && array[i] == array[i-2] && array[i] == array[i-3] && array[i] == array[i-4]){
        sum = array[i] * 5;
        return sum;
       } 
    }
return 0;
}


int main(void){
    struct Scoreboard scoreboard;
    struct Dies dies;
    int scores[18];
    int nTerninger;
    int *array;
    srand(time(NULL));

    printf("Indtast hvor mange terninger du vil kaste?\n");
    scanf("%d", &nTerninger);
    if(nTerninger < 5){
        return 1;
    }

   // 1-6 
    array = roll_multiple_dice(nTerninger);
    scoreboard.ones = ones(array, nTerninger);
    printf("Sum1: %d \n", scoreboard.ones);
    
    array = roll_multiple_dice(nTerninger);
    scoreboard.twos = twos(array, nTerninger);
    printf("Sum2: %d \n", scoreboard.twos);

    array = roll_multiple_dice(nTerninger);
    scoreboard.threes = threes(array, nTerninger);
    printf("Sum3: %d \n", scoreboard.threes);

    array = roll_multiple_dice(nTerninger);
    scoreboard.fours = fours(array, nTerninger);
    printf("Sum4: %d \n", scoreboard.fours);

    array = roll_multiple_dice(nTerninger);
    scoreboard.fives = fives(array, nTerninger);
    printf("Sum5: %d \n", scoreboard.fives);

    array = roll_multiple_dice(nTerninger);
    scoreboard.sixes = sixes(array, nTerninger);
    printf("Sum6: %d \n", scoreboard.sixes);

    scoreboard.bonus = bonus(scoreboard);
    printf("Bonus: %d \n", scoreboard.bonus);

    // Par 1 til FourOfAKind
    array = roll_multiple_dice(nTerninger);
    scoreboard.onePair = onePair(array, nTerninger);
    printf("SumPar1: %d \n", scoreboard.onePair);

    array = roll_multiple_dice(nTerninger);
    scoreboard.twoPair = twoPair(array, nTerninger);
    printf("SumPar2: %d \n", scoreboard.twoPair);

    array = roll_multiple_dice(nTerninger);
    scoreboard.threeOfAKind = threeOfAKind(array, nTerninger);
    printf("Sum x3: %d \n", scoreboard.threeOfAKind);

    array = roll_multiple_dice(nTerninger);
    scoreboard.fourOfAKind = fourOfAKind(array, nTerninger);
    printf("Sum x4: %d \n", scoreboard.fourOfAKind);
    // resten
    array = roll_multiple_dice(nTerninger);
    scoreboard.small = small(array, nTerninger);
    printf("SumSmall: %d \n", scoreboard.small);

    array = roll_multiple_dice(nTerninger);
    scoreboard.large = large(array, nTerninger);
    printf("SumLarge: %d \n", scoreboard.large);

    array = roll_multiple_dice(nTerninger);
    scoreboard.fullHouse = fullHouse(array, nTerninger);
    printf("SumFullHouse: %d \n", scoreboard.fullHouse);

    array = roll_multiple_dice(nTerninger);
    scoreboard.chance = chance(array, nTerninger);
    printf("SumChance: %d \n", scoreboard.chance);

    array = roll_multiple_dice(nTerninger);
    scoreboard.yatzy = yatzy(array, nTerninger);
    printf("SumYatzy: %d \n", scoreboard.yatzy);

    return 0;
}

int *roll_multiple_dice(int nTerninger){
    int *array = (int*) malloc(nTerninger * sizeof(int));
    for (int i = 0; i < nTerninger; i++){
        array[i] = (rand() % 6 + 1);
    }
    return array;
}

