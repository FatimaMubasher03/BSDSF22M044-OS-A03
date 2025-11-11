#ifndef SHELL_H
#define SHELL_H

int handle_builtin(char **arglist);
void execute(char **arglist);
char *read_line();
char **split_line(char *line);

#endif
