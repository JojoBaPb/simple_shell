#include "shell.h"

/* Function prototypes */
void run_shell();
void print_prompt();
void execute_command(char *command);
void handle_exit();
int is_exit_command(char *command);

int main(void)
{
	run_shell();
	return 0;
}

/* Run the shell loop */
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

/* Print the shell prompt */
void print_prompt()
{
	if (isatty(STDOUT_FILENO))
	{
		write(STDOUT_FILENO, "($) ", 4);
	}
}

/* Execute a command */
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

/* Handle the exit command */
void handle_exit()
{
	if (isatty(STDOUT_FILENO))
	{
		write(STDOUT_FILENO, "Exiting shell.\n", 15);
	}
	_exit(EXIT_SUCCESS);
}

/* Check if a command is the exit command */
int is_exit_command(char *command)
{
	return strcmp(command, "exit") == 0;
}

