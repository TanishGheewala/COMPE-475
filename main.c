/* Comments - Brief labels for non-obvious concepts. */
/* Syntax - Include directives. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "calculator.h"

#define MAX_HISTORY 20 /* Constants - Named macro. */
#define DEFAULT_HISTORY 5

int main(void)
{
    /* Syntax - Main function and block. */
    User user;

    /* Output - Meaningful printf results. */
    printf("=== Simple Calculator ===\n");

    printf("Enter your name: ");

    /* User Input - Read and validate a name. */
    if (fgets(user.name, MAX_NAME, stdin) == NULL) {
        printf("Error reading name.\n");
        return 1;
    }

    /* Strings - Safely keep a null-terminated name. */
    user.name[strcspn(user.name, "\n")] = '\0';

    /* Memory Address - & obtains the user's address. */
    User *user_ptr = &user;

    /* Pointers - Valid typed pointer dereference. */
    if (user_ptr == NULL) {
        printf("Invalid user pointer.\n");
        return 1;
    }

    printf("\nWelcome, %s!\n", user_ptr->name);
    printf("User structure address: %p\n", (void *)&user);

    int history_capacity; /* Variables - Named storage. */

    printf("\nHow many calculations should be stored? ");
    
    if (scanf("%d", &history_capacity) != 1) {
        printf("Invalid input. Using default size of %d.\n",
               DEFAULT_HISTORY);

        history_capacity = DEFAULT_HISTORY;

        /* While Loop - Clear input until newline. */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Break/Continue - Discard bad input. */
        }
    }

    /* Operators - Comparison and logical operators. */
    if (history_capacity < 1 || history_capacity > MAX_HISTORY) {
        printf("History size must be between 1 and %d.\n",
               MAX_HISTORY);

        printf("Using default size of %d.\n", DEFAULT_HISTORY);

        history_capacity = DEFAULT_HISTORY;
    }

    /* Memory Management - Allocate and check ownership. */
    Calculation *history = malloc(history_capacity * sizeof(Calculation));

    if (history == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int history_count = 0;

    /* Function Pointers - Select an operation. */
    Operation operations[4] = {
        add,
        subtract,
        multiply,
        divide
    };

    /* Arrays - Related operation symbols. */
    char symbols[4] = {
        '+',
        '-',
        '*',
        '/'
    };

    bool running = true; /* Booleans - Controls the menu. */

    /* While Loop - Repeat while the menu is active. */
    while (running) {

        int choice;

        printf("\n=== Menu ===\n");
        printf("1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Divide\n");
        printf("5. View History\n");
        printf("6. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {

            printf("Invalid input. Enter a number from 1 to 6.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Break/Continue - Skip invalid input. */
            }

            continue;
        }

        /* Switch - Choose among named cases. */
        switch (choice) {

            case 1:
            case 2:
            case 3:
            case 4: {

                int first;
                int second;

                printf("Enter two integers: ");

                if (scanf("%d %d", &first, &second) != 2) {

                    printf("Invalid numbers.\n");

                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {
                        /* Clear the remaining invalid input. */
                    }

                    continue;
                }

                if (choice == 4 && second == 0) {
                    printf("Cannot divide by zero.\n");
                    continue;
                }

                /* Type Conversion - Integers become doubles. */
                double a = (double)first;
                double b = (double)second;

                Operation selected_operation =
                    operations[choice - 1];

                if (selected_operation == NULL) {
                    printf("Invalid operation pointer.\n");
                    continue;
                }

                /* Function Parameters - Pass operands. */
                double result = selected_operation(a, b);

                printf("%.2f %c %.2f = %.2f\n",
                       a,
                       symbols[choice - 1],
                       b,
                       result);

                /* If...Else - Store or report full history. */
                if (history_count < history_capacity) {

                    history[history_count].a = a;
                    history[history_count].b = b;
                    history[history_count].result = result;
                    history[history_count].symbol =
                        symbols[choice - 1];

                    history_count++;

                } else {
                    printf("History storage is full.\n");
                }
                break;
            }

            case 5:
                print_history(history, history_count);
                break;

            case 6:

                running = false;
                break;

            default:

                printf("Invalid choice. Enter 1 through 6.\n");
                break;
        }
    }

    free(history); /* Memory Management - Release allocated memory. */

    history = NULL;

    printf("\nGoodbye, %s!\n", user_ptr->name);

    return 0;
}