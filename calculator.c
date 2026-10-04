#include <stdio.h>
#include "calculator.h"

/* Scope - File-scope static state. */
static int total_calculations = 0;

/* Functions - Define a reusable operation. */
double add(double a, double b)
{
    total_calculations++;
    return a + b;
}

double subtract(double a, double b)
{
    total_calculations++;
    return a - b;
}

double multiply(double a, double b)
{
    total_calculations++;
    return a * b;
}

double divide(double a, double b)
{
    total_calculations++;
    return a / b;
}

/* Function Parameters - Receive history and count. */
void print_history(const Calculation *history, int count)
{
    printf("\n--- Calculation History ---\n");

    if (count == 0) {
        printf("No calculations yet.\n");
        return;
    }

    /* For Loop - Process each history entry. */
    for (int i = 0; i < count; i++) {
        printf("%d: %.2f %c %.2f = %.2f\n",
               i + 1,
               history[i].a,
               history[i].symbol,
               history[i].b,
               history[i].result);
    }
}