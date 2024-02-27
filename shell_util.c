#include "shell.h"

/**
 * print_prompt - Function to print the shell prompt
 */
void print_prompt()
{
	printf("($) ");
	fflush(stdout);
}

/**
 * remove_newline - Function to remove the newline character from a string
 * @str: The string to process
 */
void remove_newline(char *str)
{
	if (str[strlen(str) - 1] == '\n')
	{
		str[strlen(str) - 1] = '\0';
	}
}

