#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void run_shell(void);
void print_prompt(void);
void remove_newline(char *str);
void execute_command(char *command);
void handle_eof(void);
void handle_exit(void);
int is_exit_command(char *command);

#endif /* SHELL_H */

