#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(){
    float a, b, c;
    int valid_input = 0;

    // get input from user and ensure it is valid
    do {
        printf("Enter coefficient of a, b, c: ");
        valid_input = scanf("%f %f %f", &a, &b, &c);
        while (getchar() != '\n' ); // clear buffer
        if (valid_input != 3) {
            printf("Invalid input. Please try again.\n");
        }
        if (a == 0) {
            printf("a cannot be zero. Please try again.\n");
            valid_input = 0;
        }
    } while (valid_input != 3);
    printf("a = %.2f, b = %.2f, c = %.2f\n", a, b, c);
    
    return 0;
}
// it skips last output