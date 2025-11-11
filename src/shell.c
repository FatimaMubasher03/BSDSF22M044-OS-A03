#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int handle_builtin(char **arglist) {
    if (arglist[0] == NULL) return 0; // no command entered

    if (strcmp(arglist[0], "exit") == 0) {
        printf("Exiting shell...\n");
        exit(0);
    }
    else if (strcmp(arglist[0], "cd") == 0) {
        if (arglist[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(arglist[1]) != 0) {
                perror("cd");
            }
        }
        return 1; // handled
    }
    else if (strcmp(arglist[0], "help") == 0) {
        printf("Built-in commands:\n");
        printf("  exit     - terminate the shell\n");
        printf("  cd DIR   - change directory to DIR\n");
        printf("  help     - show this message\n");
        printf("  jobs     - list background jobs (not yet implemented)\n");
        return 1; // handled
    }
    else if (strcmp(arglist[0], "jobs") == 0) {
        printf("Job control not yet implemented.\n");
        return 1; // handled
    }

    return 0; // not a built-in
}
#define MAX_LINE 1024
#define MAX_ARGS 64

char *read_line() {
    char *line = malloc(MAX_LINE);
    if (!line) { perror("malloc"); exit(1); }
    if (fgets(line, MAX_LINE, stdin) == NULL) {
        printf("\n"); // handle Ctrl+D
        exit(0);
    }
    line[strcspn(line, "\n")] = 0; // remove newline
    return line;
}

char **split_line(char *line) {
    char **args = malloc(MAX_ARGS * sizeof(char *));
    char *token;
    int i = 0;
    token = strtok(line, " ");
    while (token != NULL && i < MAX_ARGS-1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return args;
}
