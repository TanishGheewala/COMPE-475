#ifndef CALCULATOR_H
#define CALCULATOR_H

#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
} User;

typedef struct {
    double a;
    double b;
    double result;
    char symbol;
} Calculation;

typedef double (*Operation)(double, double);

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

void print_history(const Calculation *history, int count);

#endif