/**********************************************************************************************************************
                                                Quadratic Equation                                                        
                                                ==================    
In this project, the task is to design a program that solves a quadratic equation of the form ax^2 + bx + c = 0, where 
'a', 'b' and 'c' are user-defined and'x' is unknown variable. 'a', 'b' and 'c' are real numbers and a cannot be 0. The
 program prompts the user to input the coefficients a, b, and c, and then calculates and displays a table which shows
input of the user, value of the discriminat and root values and the type of root two roots of the equation. 

* Programe Name: main.c
* Author: Lim Cai Yin, Lee Wen Jie, Joseph Chong Kien Chen                                                            
* Date: 28 Februrary 2023                                                                                             
************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to get a double input from the user

int get_input(const char* prompt, double* value, int check_a) {
    char input[256]; 
    printf("%s", prompt); 
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Error: Failed to read input.\n");
        return 0;
    }
    char* endptr; // pointer to the end of the string
    double num = strtod(input, &endptr); // strtod is used to convert the string to a double
    // Check if the input is a valid double, 
    if (endptr == input || *endptr != '\n') {
        printf("Error: Invalid input format. Please make sure that the input does not have characters.\n");
        return 0;
    }
    // if a is 0, input is invalid, check_a is flag to check if a is 0
    if (check_a && num ==0){
        printf("Error: Invalid cannot put 0 for a.\n");
        return 0;
    }
    *value = num;
    return 1;
}

/** Function to solve a quadratic equation of the form ax^2 + bx + c = 0
 * @param a The coefficient of x^2
 * @param b The coefficient of x
 * @param c The constant term
 * @param root1 Pointer to the first root
 * @param root2 Pointer to the second root
 * @param discriminant The discriminant of the equation
 * @return 1 if two real roots, 2 if one real root, 3 if two complex roots otherwise 0
 */

int solve_quadratic(double a, double b, double c, double* root1, double* root2, double discriminant) {
    if (discriminant > 0) {
        // Two real roots
        *root1 = (-b + sqrt(discriminant)) / (2 * a);
        *root2 = (-b - sqrt(discriminant)) / (2 * a);
        return 1;
    } else if (discriminant == 0) {
        // One real root
        *root1 = -b / (2 * a);
        *root2 = *root1;
        return 2;
    } else {
        // Two complex roots
        *root1 = -b / (2 * a);
        *root2 = sqrt(-discriminant) / (2 * a);
        return 3;
    }
}

/** Function to determine the type of roots and store the value of the roots in a string
 * @param root1 The first root
 * @param root2 The second root
 * @param status The status code returned from solve_quadratic
 * @param root_type Pointer to the root type string
 * @param x1 Pointer to the string to store the value of root1
 * @param x2 Pointer to the string to store the value of root2
 */
void determine_roots(double root1, double root2, int status, char** root_type, char *x1, char *x2){
    switch(status){
        case 1: 
            *root_type = strdup("Real and different"); // strdup is used to copy the string to the pointer
            sprintf(x1, "%.2lf", root1); // sprintf is used to convert the double to a string
            sprintf(x2, "%.2lf", root2);
            break;
        case 2:
            *root_type = strdup("Real and equal");
            sprintf(x1, "%.2lf", root1);
            sprintf(x2, "%.2lf", root2);
            break;
        case 3:
            *root_type = strdup("Complex and different");
            sprintf(x1, "%.2lf + %.2lfi", root1, root2);
            sprintf(x2, "%.2lf - %.2lfi", root1, root2);
            break;
        default:
            printf("Error: Invalid status code returned from solve_quadratic.\n");
            break;
    }
}

/** Function to print the roots of a quadratic equation in a table*/
void print_table(double a, double b, double c, char* x1, char* x2, char **root_type, double discriminant) {
    printf("+-----------+-----------+-----------+----------------+----------------+-----------------------+----------------+\n");
    printf("|  Input a  |  Input b  |  Input c  |     Root 1     |     Root 2     |          Type         |  Discriminant  |\n");
    printf("+-----------+-----------+-----------+----------------+----------------+-----------------------+----------------|\n");
    for (int i = 0; i < 1; i++) {
        printf("| %9.2f | %9.2f | %9.2f | %14s | %14s | %21s | %14.2f |\n", a, b, c, x1, x2, *root_type, discriminant);
        printf("+-----------+-----------+-----------+----------------+----------------+-----------------------+----------------|\n\n");
    }
}

int main() {
    // Declare variables
    double a, b, c, root1, root2, discriminant;
    char *root_type; 
    char x1[20]; // string to store the value of root1
    char x2[20]; // string to store the value of root2
    int max_attempts = 3;
    int num_attempts=0; 

    printf("Quadratic Equation Solver:  ax%s + bx + c = 0\n", "\u00B2"); // \u00B2 is used to print the superscript 2
    
    // Loop until the user has entered valid inputs or has exceeded the number of attempts
    while (num_attempts < 3) {
        printf("You have %d attempt(s) left.\n", max_attempts - num_attempts);
        if (!get_input("Enter the coefficient of x² (a): ", &a, 1)) {
            num_attempts++;
            continue;
        }
        if (!get_input("Enter the coefficient of x (b): ", &b, 0)) {
            num_attempts++;
            continue;
        }
        if (!get_input("Enter the constant term (c): ", &c, 0)) {
            num_attempts++;
            continue;
        }
        break;
    }

    // Check if the user has exceeded the number of attempts
    if (num_attempts == 3){
        printf("Too many incorrect attempts. Program terminating.\n");
        return 1;
    }
    
    discriminant = b * b - 4 * a * c;
    
    // if the user has not exceeded the number of attempts, print the equation, discriminant and roots
    printf("\nThe equation is: %.2lfx%s %+.2lfx %+.2lf = 0\n", a, "\u00B2", b, c); // %+.2lf is used to print the sign of the constant term
    printf("Discriminant(d) = b²-4ac: (%.2lf)²-4(%.2lf)(%.2lf)= %.2lf\n", b,a,c,discriminant);
    printf("Roots(x) = (-b ± √b²-4ac)/2a: -(%.2lf) ± √%.2lf/2(%.2lf)\n\n", b,discriminant,a);

    // Solve the quadratic equation and get the status code
    int status = solve_quadratic(a, b, c, &root1, &root2, discriminant);

    // determine the roots and root values
    determine_roots(root1, root2, status, &root_type, x1, x2);
    
    // Print the table of inputs and outputs
    print_table(a, b, c, x1, x2, &root_type,discriminant);

    // End of program
    printf("Program completed successfully!\n");
    
    // Free the memory allocated for root_type
    free (root_type);

    return 0;
}