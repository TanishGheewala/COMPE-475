#ifndef CALCULATOR_H
#define CALCULATOR_H

#define MAX_NAME 50 /* Constants - Fixed name limit. */

/* Structures - Group related user data. */
typedef struct {
    char name[MAX_NAME];
} User;

/* Data Types - Floating-point and character fields. */
typedef struct {
    double a;
    double b;
    double result;
    char symbol;
} Calculation;

/* Function Pointers - Reusable operation type. */
typedef double (*Operation)(double, double);

/* Function Declaration - Declarations before use. */
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

/* Functions - Reusable history display function. */
void print_history(const Calculation *history, int count);

#endif