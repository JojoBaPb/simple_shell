#include "shell.h"

/**
 * run_shell - Function to run the shell
 */

int main(void)
{
	    run_shell();
	        return 0;
}

void run_shell()
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		print_prompt();

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			handle_eof();
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

