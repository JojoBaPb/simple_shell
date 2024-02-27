#include "shell.h"

/**
 * execute_command - Function to execute a command
 * @command: The command to executed
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
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, NULL) < 0)
		{
			perror("hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

