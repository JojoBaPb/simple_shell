#include "shell.h"

/* Remove newline character from a string */
void remove_newline(char *str)
{
	int length = strlen(str);
	if (length > 0 && str[length - 1] == '\n')
	{
		str[length - 1] = '\0';
	}
}
