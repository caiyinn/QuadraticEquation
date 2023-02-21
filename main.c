#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// #include <ctype.h>

int main() {
    float a, b, c, discriminant, root1, root2, realPart, imagPart;
    int valid_input = 0; //flag for valid input
    // get input from user and ensure it is valid
    do {
        printf("Enter coefficient of a, b, c: ");
        valid_input = scanf("%f %f %f", &a, &b, &c);
        while (getchar() != '\n' ); // clear buffer
        if (valid_input != 3) {
            printf("Invalid input, make sure that there is no characters in the input. Please try again.\n");
        }
        if (a == 0) {
            printf("a cannot be zero. Please try again.\n");
            valid_input = 0;
        }
    } while (valid_input != 3);
    
    // calculate discriminant
    discriminant = b*b - 4*a*c;

    printf("discriminant = %.2f\n", discriminant);
    // condition for real and different roots
    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("real and different roots\n");
        printf("root1 = %.2lf and root2 = %.2lf", root1, root2);
    }

    // condition for real and equal roots
    else if (discriminant == 0) {
        root1 = root2 = -b / (2 * a);
        printf("real and equal roots\n");
        printf("root1 = root2 = %.2lf;", root1);
    }

    // if roots are not real
    else {
        realPart = -b / (2 * a);
        imagPart = sqrt(-discriminant) / (2 * a);
        printf("no real roots\n");
        printf("root1 = %.2lf+%.2lfi and root2 = %.2f-%.2fi", realPart, imagPart, realPart, imagPart);
    }

    return 0;
} 

// git push origin cy
//gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror -Wconversion -o test test.c