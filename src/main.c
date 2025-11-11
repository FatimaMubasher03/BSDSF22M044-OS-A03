#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main() {
    char *line;
    char **arglist;

    while (1) {
        printf("FCIT> ");
        fflush(stdout);

        line = read_line();
        arglist = split_line(line);

        // check built-in commands first
        if (!handle_builtin(arglist)) {
            execute(arglist); // run external command if not built-in
        }

        free(line);
        free(arglist);
    }

    return 0;
}
