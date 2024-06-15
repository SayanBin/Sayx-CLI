#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_COMMAND_LENGTH 20
#define MAX_ARG_LENGTH 100

// ANSI color codes
#define RESET_COLOR "\x1B[0m"
#define GREEN_COLOR "\x1B[32m"
#define BRIGHT_GREEN_COLOR "\x1B[92m"
#define ASPARAGUS_COLOR "\x1B[38;5;64m"  // New asparagus color

void print_border() {
    printf(BRIGHT_GREEN_COLOR "+-----------------------------------------------+\n" RESET_COLOR);
}

void print_header(const char *title) {
    print_border();
    printf(BRIGHT_GREEN_COLOR "| %-45s |\n" RESET_COLOR, title);
    print_border();
}

// Function to list files and directories in the current directory
void list_files() {
    DIR *dir;
    struct dirent *entry;

    print_header("File List");

    dir = opendir(".");
    if (dir == NULL) {
        perror(ASPARAGUS_COLOR "Unable to open directory" RESET_COLOR);
        return;
    }

    printf(BRIGHT_GREEN_COLOR);
    while ((entry = readdir(dir)) != NULL) {
        printf("| %-45s |\n", entry->d_name);
    }
    printf(RESET_COLOR);

    closedir(dir);
    print_border();
}

// Function to create a new directory
void create_directory(const char *dirname) {
    print_header("Create Directory");

    if (mkdir(dirname, 0777) == 0) {
        printf(BRIGHT_GREEN_COLOR "| Directory '%-37s' created. |\n" RESET_COLOR, dirname);
    } else {
        perror(ASPARAGUS_COLOR "Error creating directory" RESET_COLOR);
    }

    print_border();
}

// Function to remove a file or directory
void remove_item(const char *name) {
    print_header("Remove Item");

    if (remove(name) == 0) {
        printf(BRIGHT_GREEN_COLOR "| Item '%-41s' removed. |\n" RESET_COLOR, name);
    } else {
        perror(ASPARAGUS_COLOR "Error removing item" RESET_COLOR);
    }

    print_border();
}

// Function to display a simple text editor
void text_editor() {
    print_header("Text Editor");

    printf(ASPARAGUS_COLOR "| Launching Text Editor...                     |\n" RESET_COLOR);
    printf(BRIGHT_GREEN_COLOR "| Enter text below (press Ctrl+D to save and exit): |\n" RESET_COLOR);

    FILE *file = fopen("sayxfile", "w");
    if (file == NULL) {
        perror(ASPARAGUS_COLOR "Error opening file" RESET_COLOR);
        return;
    }

    char ch;
    while ((ch = getchar()) != EOF) {
        fputc(ch, file);
    }

    fclose(file);
    printf(BRIGHT_GREEN_COLOR "| Text saved to 'sayxfile'.                     |\n" RESET_COLOR);
    print_border();
}

// Function to display a simple calculator
void calculator() {
    print_header("Calculator");

    double num1, num2, result;
    char operator;

    printf(BRIGHT_GREEN_COLOR "| Enter expression (e.g., 5 + 3):              |\n" RESET_COLOR);
    if (scanf("%lf %c %lf", &num1, &operator, &num2) != 3) {
        fprintf(stderr, ASPARAGUS_COLOR "| Error: Invalid input.                       |\n" RESET_COLOR);
        print_border();
        return;
    }

    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0)
                result = num1 / num2;
            else {
                fprintf(stderr, ASPARAGUS_COLOR "| Error: Division by zero.                   |\n" RESET_COLOR);
                print_border();
                return;
            }
            break;
        default:
            fprintf(stderr, ASPARAGUS_COLOR "| Error: Invalid operator.                   |\n" RESET_COLOR);
            print_border();
            return;
    }

    printf(BRIGHT_GREEN_COLOR "| Result: %-41.2lf |\n" RESET_COLOR, result);
    print_border();
}

// Function to view contents of a file
void file_viewer(const char *filename) {
    print_header("File Viewer");

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror(ASPARAGUS_COLOR "Error opening file" RESET_COLOR);
        print_border();
        return;
    }

    printf(BRIGHT_GREEN_COLOR);
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf(RESET_COLOR);

    fclose(file);
    print_border();
}

// Function to display a simple calendar
void calendar() {
    print_header("Calendar");

    printf(ASPARAGUS_COLOR "| Launching Calendar...                       |\n" RESET_COLOR);
    if (system("cal") == -1) {
        perror(ASPARAGUS_COLOR "Error launching calendar" RESET_COLOR);
    }

    print_border();
}

// Function to handle todo list
void todo_list() {
    print_header("Todo List");

    printf(ASPARAGUS_COLOR "| Launching Todo List...                      |\n" RESET_COLOR);
    // Placeholder for todo list implementation
    print_border();
}

// Function to display the list of available commands
void display_help() {
    print_header("Help");

    printf(GREEN_COLOR "| help: Display this help message             |\n");
    printf("| list: List files                            |\n");
    printf("| add [name]: Create directory                |\n");
    printf("| del [name]: Remove file/directory           |\n");
    printf("| edit: Launch Text Editor                    |\n");
    printf("| calc: Launch Calculator                     |\n");
    printf("| view [file]: View file contents             |\n");
    printf("| calendar: Launch Calendar                   |\n");
    printf("| todo: Launch Todo List                      |\n");
    printf("| print [message]: Print a message            |\n");
    printf("| exit: Exit the program                      |\n" RESET_COLOR);

    print_border();
}

// Function to handle user input and execute commands
void handle_input(char *input) {
    char command[MAX_COMMAND_LENGTH];
    char argument[MAX_ARG_LENGTH];

    // Initialize command and argument to empty strings
    command[0] = '\0';
    argument[0] = '\0';

    sscanf(input, "%s %[^\n]", command, argument);

    if (strcmp(command, "help") == 0) {
        display_help();
    } else if (strcmp(command, "list") == 0) {
        list_files();
    } else if (strcmp(command, "add") == 0) {
        if (strlen(argument) > 0) {
            create_directory(argument);
        } else {
            fprintf(stderr, ASPARAGUS_COLOR "| Error: Missing directory name.              |\n" RESET_COLOR);
            print_border();
        }
    } else if (strcmp(command, "del") == 0) {
        if (strlen(argument) > 0) {
            remove_item(argument);
        } else {
            fprintf(stderr, ASPARAGUS_COLOR "| Error: Missing file or directory name.      |\n" RESET_COLOR);
            print_border();
        }
    } else if (strcmp(command, "edit") == 0) {
        text_editor();
    } else if (strcmp(command, "calc") == 0) {
        calculator();
    } else if (strcmp(command, "view") == 0) {
        if (strlen(argument) > 0) {
            file_viewer(argument);
        } else {
            fprintf(stderr, ASPARAGUS_COLOR "| Error: Missing file name.                   |\n" RESET_COLOR);
            print_border();
        }
    } else if (strcmp(command, "calendar") == 0) {
        calendar();
    } else if (strcmp(command, "todo") == 0) {
        todo_list();
    } else if (strcmp(command, "print") == 0) {
        printf(BRIGHT_GREEN_COLOR "| %-45s |\n" RESET_COLOR, argument);
        print_border();
    } else if (strcmp(command, "exit") == 0) {
        printf(BRIGHT_GREEN_COLOR "| Exiting Sayx CLI...                         |\n" RESET_COLOR);
        print_border();
        exit(0);
    } else {
        fprintf(stderr, ASPARAGUS_COLOR "\n" RESET_COLOR, command);
    }
}

// Main function
int main() {
    char input[MAX_COMMAND_LENGTH + MAX_ARG_LENGTH + 2];
    printf(BRIGHT_GREEN_COLOR"█ █ █ █▀▀ █   █▀▀ █▀█ █▄ ▄█ █▀▀\n");
    printf(GREEN_COLOR"▀▄▀▄▀ ██▄ █▄▄ █▄▄ █▄█ █ ▀ █ ██▄\n");
    printf("\n");
    print_header("Sayx CLI 4");
    printf(BRIGHT_GREEN_COLOR "| Welcome to Sayx CLI 4                      |\n" RESET_COLOR);
    printf(BRIGHT_GREEN_COLOR "| Type 'help' for a list of commands.         |\n" RESET_COLOR);
    print_border();
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, ASPARAGUS_COLOR "Error reading input.\n" RESET_COLOR);
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = 0;

        handle_input(input);
    }

    return 0;
}

