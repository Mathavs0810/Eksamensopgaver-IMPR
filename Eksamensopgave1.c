#include <stdio.h>
#include <math.h>
#include <string.h>

void scan_data(double *operand, char *operator);
void do_next_op(char operator, double operand, double *accumulator);
void run_calculator();
int is_binary_operator(char operator);

int main(void){
    run_calculator();
}

int is_binary_operator(char operator){ // Returnere 1 hvis den er lig med følgende symboler (De binære) og 0 hvis den er lig med Unære 
    return (operator == '+' || operator =='-' ||operator == '*' || operator == '/' || operator == '^');
} 

void scan_data(double *operand, char *operator){
    printf("Indtast en operator: \n");
    scanf(" %c", operator); 

    if(is_binary_operator(*operator)){ // Hvis funktionen modtager 1, vil den køre if-statementet. Hvis den modtager 0, så er betingelsen ikke opfyldt. Dette er tilsvarende til en boolean.vb
            printf("Indtast en operand: \n");
            scanf("%lf", operand);
    }


    /* switch(*operator){
        case '+':
            printf("Indtast en operand: \n");
            scanf("%lf", operand);
            break;
        case '-':
            printf("Indtast en operand: \n");
            scanf("%lf", operand);
            break;
        case '*':
            printf("Indtast en operand: \n");
            scanf("%lf", operand);
            break;
        case '/':
            printf("Indtast en operand: \n");
            scanf("%lf", operand);
            break;
        case '^':
            printf("Indtast en operand: \n");
            scanf("%lf", operand);
            break;
        case '#':
            *operand = 0.0;
            break;
        case '%':
            *operand = 0.0;
            break;
        case '!':
            *operand = 0.0;
            break;
    } */
}

void do_next_op(char operator, double operand, double *accumulator){
    // Binære:
    switch(operator){
        case '+':
            *accumulator += operand;
            printf("Result so far is: %lf \n", *accumulator);
            break;
        case '-':
            *accumulator -= operand;
            printf("Result so far is: %lf \n", *accumulator);
            break;
        case '*':
            *accumulator *= operand;
            printf("Result so far is: %lf \n", *accumulator);
            break;
        case '/':
            if(operand == 0){
                printf("Result so far is: %lf \n", *accumulator);
                break;
            } else {
                *accumulator /= operand;
                printf("Result so far is: %lf \n", *accumulator);
                break;
        }
        case '^':
            *accumulator = pow(*accumulator, operand);
            printf("Result so far is: %lf \n", *accumulator);
            break;
    }

    //Unære: 
    switch(operator){
        case '#':
            if(*accumulator <= 0){
                printf("Result so far is: %lf \n", *accumulator);
                break;
            } else {
            *accumulator = sqrt(*accumulator);
            printf("Result so far is: %lf \n", *accumulator);
            break;
            }
        case '%':
            *accumulator *=-1;
            printf("Result so far is: %lf \n", *accumulator);
            break;
        case '!':
            *accumulator = 1 / *accumulator;
            printf("Result so far is: %lf \n", *accumulator);
            break;
        case 'q':
        printf("Final result is: %lf \n", *accumulator);
            break;
    }
}

void run_calculator(){
    double accumulator = 0.0;
    double operand;
    char operator;

do {
    scan_data(&operand, &operator);
    do_next_op(operator, operand, &accumulator);

} while (strcmp(&operator, "q") != 0); // Hvis operatoren er lig q, så outputter funktionen "strcmp" 0, og derfor slutter programmet. 
}


/* Binære Operationer
    +    for addition af akkumulatoren med operanden
    -    for subtraktion af akkumulatoren med operanden
    *    for multiplikation af akkumulatoren med operanden
    /    for division af akkumulatoren med operanden
    ^    for potensopløftning af akkumulatoren med operanden
*/
/* Unære operatorer
  #    for kvadratroden af akkumulatoren
  %    for at vende fortegnet af akkumulatoren
  !    for at dividere 1 med akkumulatoren
  q    for at afslutte regnemaskinen med slutresultatet
*/