#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "calculator.h"

#define MAX_HISTORY 20
#define DEFAULT_HISTORY 5

int main(void)
{
    User user;

    printf("=== Simple Calculator ===\n");

    printf("Enter your name: ");

    if (fgets(user.name, MAX_NAME, stdin) == NULL) {
        printf("Error reading name.\n");
        return 1;
    }

    // Remove newline added by fgets
    user.name[strcspn(user.name, "\n")] = '\0';

    User *user_ptr = &user;

    if (user_ptr == NULL) {
        printf("Invalid user pointer.\n");
        return 1;
    }

    printf("\nWelcome, %s!\n", user_ptr->name);
    printf("User structure address: %p\n", (void *)&user);

    int history_capacity;

    printf("\nHow many calculations should be stored? ");
    
    if (scanf("%d", &history_capacity) != 1) {
        printf("Invalid input. Using default size of %d.\n",
               DEFAULT_HISTORY);

        history_capacity = DEFAULT_HISTORY;

        // Clear invalid characters from input buffer
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            // discard input
        }
    }

    if (history_capacity < 1 || history_capacity > MAX_HISTORY) {
        printf("History size must be between 1 and %d.\n",
               MAX_HISTORY);

        printf("Using default size of %d.\n", DEFAULT_HISTORY);

        history_capacity = DEFAULT_HISTORY;
    }

    Calculation *history = malloc(history_capacity * sizeof(Calculation));

    if (history == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int history_count = 0;

    Operation operations[4] = {
        add,
        subtract,
        multiply,
        divide
    };

    char symbols[4] = {
        '+',
        '-',
        '*',
        '/'
    };

    bool running = true;

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
                // discard invalid input 
            }

            continue;
        }

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
                        // discard invalid input
                    }

                    continue;
                }

                if (choice == 4 && second == 0) {
                    printf("Cannot divide by zero.\n");
                    continue;
                }

                double a = (double)first;
                double b = (double)second;

                Operation selected_operation =
                    operations[choice - 1];

                if (selected_operation == NULL) {
                    printf("Invalid operation pointer.\n");
                    continue;
                }

                double result = selected_operation(a, b);

                printf("%.2f %c %.2f = %.2f\n",
                       a,
                       symbols[choice - 1],
                       b,
                       result);

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

    free(history);

    history = NULL;

    printf("\nGoodbye, %s!\n", user_ptr->name);

    return 0;
}