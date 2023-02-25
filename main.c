#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "test.h"
// #include <ctype.h>

int main() {
    float a, b, c, discriminant, root1, root2, realPart, imagPart;
    int valid_input = 0; //flag for valid input
    int count = 0; // count number of input
    char name[10][20] = {"a","b","c", "Discriminant", "Type of Equation", "Number of Roots", "Root 1", "Root 2", "Real Number", "Imaginary Number"}; 
    // get input from user and ensure it is valid
    do {
        printf("Enter coefficient of a, b, c: ");
        valid_input = scanf("%f %f %f", &a, &b, &c);
        while (getchar() != '\n' ); // clear buffer
        if (valid_input != 3) {
            printf("Invalid input, make sure that there is no characters in the input. Please try again.\n");
        }
        // check if a is zero
        if (a == 0) {
            printf("a cannot be zero. Please try again.\n");
            valid_input = 0;
        }
        // check if user has entered invalid input 5 times
        if (count == 4) {
            printf("You have entered invalid input 5 times. Program will exit now.\n");
            exit(0);
        }
        count++;
    } while (valid_input != 3);
    
    // calculate discriminant
    discriminant = b*b - 4*a*c;

    printf("discriminant = %.2f\n", discriminant);
    // condition for real and different roots
    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("real and different roots\n");
        printf("root1 = %.2lf and root2 = %.2lf\n", root1, root2);
    }

    // condition for real and equal roots
    else if (discriminant == 0) {
        root1 = root2 = -b / (2 * a);
        printf("real and equal roots\n");
        printf("root1 = root2 = %.2lf\n;", root1);
    }

    // if roots are not real
    else {
        realPart = -b / (2 * a);
        imagPart = sqrt(-discriminant) / (2 * a);
        printf("no real roots\n");
        printf("root1 = %.2lf+%.2lfi and root2 = %.2f-%.2fi\n", realPart, imagPart, realPart, imagPart);
    }
    // plot table
    // printf("+==================================================================+\n");
    // printf("|          Quadratic Equation: %.2lfx^2  %.2lfx  %.2lf = 0          |\n", a, b, c);
    // printf("+=========+=========+=========+==================+=================+\n");
    // for (int i=0; i<1; i++) {
    //     printf("%s", name[1]);
    //     printf("| %+11s     |%+11s     |%+11s     |%+11s     |%+11s     |%+11s     |%+11s     |%+11s     |%+11s     |%+11s     |\n", name[1], name[2], name[3], name[4], name[5], name[6], name[7], name[8], name[9]);
        
    // }
    // plot the graph
    // init_grid();
    // for (float x = -5; x <= 5; x += 0.1) {
    //     float y = a*x*x + b*x + c;
    //     plot(rintf(x*10), rintf(y*8));
    // }
    // show_grid();

    return 0;
} 

// git push origin cy
//gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror -Wconversion -o test test.c