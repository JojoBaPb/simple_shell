#include "shell.h"

/**
 * run_shell - Run the shell loop
 *
 * Return: function
 */

void run_shell(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		print_prompt();

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			handle_exit();
			break;
		}

		remove_newline(command);

		if (is_exit_command(command))
		{
			handle_exit();
			break;
		}

		execute_command(command);
	}
}

/**
 * print_prompt - Print the shell prompt
 *
 * Return: None
 */

void print_prompt(void)
{
	if (isatty(STDOUT_FILENO))
	{
		write(STDOUT_FILENO, "($) ", 4);
	}
}

/**
 * execute_command - Execute a command
 * @command: command provided
 *
 * Return: None
 */

void execute_command(char *command)
{
	pid_t pid;
	int status;

	char *args[MAX_ARGS];
	int i = 1;

	args[0] = strtok(command, " ");
	while ((args[i] = strtok(NULL, " ")) != NULL && i < MAX_ARGS - 1)
	{
		i++;
	}
	args[i] = NULL;

	pid = fork();

	if (pid < 0)
	{
		perror("hsh");
		_exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, NULL) < 0)
		{
			perror("hsh");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * handle_exit - Handle the exit command
 *
 * Return: None
 */

void handle_exit(void)
{
	if (isatty(STDOUT_FILENO))
	{
		write(STDOUT_FILENO, "Exiting shell.\n", 15);
	}
	_exit(EXIT_SUCCESS);
}

/**
 * is_exit_command - Check if a command is the exit command
 * @command: command provided
 *
 * Return: function
 */

int is_exit_command(char *command)
{
	return (strcmp(command, "exit") == 0);
}
