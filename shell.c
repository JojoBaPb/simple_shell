#include "shell.h"

/**
 * execute_command - Execute a command.
 * @command: The command to execute.
 */
void execute_command(char *command);

/**
 * handle_exit - Handle the exit command.
 */
void handle_exit();

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	run_shell();
	return 0;
}

/**
 * run_shell - Run the shell loop.
 */
void run_shell()
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
 * print_prompt - Print the shell prompt.
 */
void print_prompt()
{
	if (isatty(STDOUT_FILENO))
	{
		write(STDOUT_FILENO, "($) ", 4);
	}
}

/**
 * execute_command - Execute a command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;

	char *args[MAX_ARGS];
	int i = 0;

	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	
	args[i] = strtok(command, " ");
	while (args[i] != NULL && i < MAX_ARGS - 1)
	{
		i++;
		args[i] = strtok(NULL, " ");
	}

	while (dir != NULL)
	{
		char command_path[MAX_COMMAND_LENGTH];
		snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);

		if (access(command_path, X_OK) == 0)
		{
			pid = fork();

			if (pid < 0)
			{
				perror("hsh");
				_exit(EXIT_FAILURE);
			}

			if (pid == 0)
			{
				if (execve(command_path, args, NULL) < 0)
				{
					perror("hsh");
					_exit(EXIT_FAILURE);
				}
			}
			else
			{
				waitpid(pid, &status, 0);
			}

			break;
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);

	if (dir == NULL)
	{
		printf("%s: command not found\n", args[0]);
	}
}

/**
 * handle_exit - Handle the exit command.
 */
void handle_exit()
{
	if (isatty(STDOUT_FILENO))
	{
		write(STDOUT_FILENO, "Exiting shell.\n", 15);
	}
	_exit(EXIT_SUCCESS);
}

/**
 * is_exit_command - Check if a command is the exit command.
 * @command: The command to check.
 *
 * Return: 1 if it is the exit command, 0 otherwise.
 */
int is_exit_command(char *command)
{
	return strcmp(command, "exit") == 0;
}

