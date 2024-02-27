#include "shell.h"

/**
 * handle_eof - Function to handle end of file
 */
void handle_eof()
{
	printf("\n");
}

/**
 * handle_exit - Function to handle exit command
 */
void handle_exit()
{
	printf("Exiting shell.\n");
}

/**
 * is_exit_command - Function to check if a command is "exit"
 * @command: The command to check
 * Return: 1 if the command is "exit", 0 otherwise
 */
int is_exit_command(char *command)
{
	return strcmp(command, "exit") == 0;
}

