#include <stdio.h>
#include "calculator.h"

static int total_calculations = 0;

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

void print_history(const Calculation *history, int count)
{
    printf("\n--- Calculation History ---\n");

    if (count == 0) {
        printf("No calculations yet.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%d: %.2f %c %.2f = %.2f\n",
               i + 1,
               history[i].a,
               history[i].symbol,
               history[i].b,
               history[i].result);
    }
}