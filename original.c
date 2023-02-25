#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to get a double input from the user
int get_input(const char* prompt, double* value, int check_a) {
    char input[256];
    int attempts = 0 ;
    printf("%s", prompt);
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Error: Failed to read input.\n");
        return 0;
    }
    char* endptr;
    double num = strtod(input, &endptr);
    if (endptr == input || *endptr != '\n') {
        printf("Error: Invalid input format. Please make sure that the input does not have characters.\n");
        return 0;
    }
    if (check_a && num ==0){
        printf("Error: Invalid cannot put 0 for a.\n");
        return 0;
    }
    *value = num;
    return 1;
    printf("Error: Too many failed attempts. Exiting program.\n");
    exit(1);  // Exit the program with an error code    
}

// Function to solve a quadratic equation of the form ax^2 + bx + c = 0
int solve_quadratic(double a, double b, double c, double* root1, double* root2) {
    double discriminant = b * b - 4 * a * c;
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

// Function to print the roots of a quadratic equation
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

// Function to print the roots of a quadratic equation in a table
void print_table(double a, double b, double c, char* x1, char* x2, char **root_type) {
    printf("+---------+---------+---------+----------------+----------------+-----------------------+\n");
    printf("| Input a | Input b | Input c |     Root 1     |     Root 2     |          Type         |\n");
    printf("+---------+---------+---------+----------------+----------------+-----------------------+\n");
    int str_len = strlen(*root_type) + 1;
    for (int i = 0; i < 1; i++) {
        printf("| %6.2f  | %6.2f  | %6.2f  | %14s | %14s | %21s | \n", a, b, c, x1, x2, *root_type);
        printf("+---------+---------+---------+----------------+----------------+-----------------------+\n");
    }
}

// Main function
int main() {
    double a, b, c, root1, root2;
    int choice;
    char *root_type;
    char x1[20];
    char x2[20];
    int max_attempts = 3;

    printf("Quadratic Equation Solver:  ax2 + bx + c = 0\n");
    int count=0, num_attempts=0;
    while (num_attempts < 3) {
        printf("You have %d attempt(s) left.\n", max_attempts - num_attempts);
        if (!get_input("Enter the coefficient of x^2 (a): ", &a, 1)) {
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
    
    printf("\nThe equation is: %.2lfx^2 + %.2lfx + %.2lf = 0\n", a, b, c);

    // Solve the quadratic equation
    int status = solve_quadratic(a, b, c, &root1, &root2);

    // determine the roots
    determine_roots(root1, root2, status, &root_type, x1, x2);

    // Print the table
    print_table(a, b, c, x1, x2, &root_type);
    
    // Free the memory allocated for root_type
    free (root_type);

    return 0;
}