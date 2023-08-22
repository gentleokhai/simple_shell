#include "myheader.h"

/**
 * quit - exits shell
 * @tok_command: Entered command
 *
 * Return: void
 */

void quit(char **tok_command)
{
	int number_token = 0, agg;

	for (; tok_command[number_token] != NULL; number_token++);
	if (number_token == 1)
	{
		free(line);
		free(tok_command);
		free(commands);
		exit(status);
	}
	else if (number_token == 2)
	{
		agg = _atoi(tok_command[1]);
		if (agg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1-> exit -> illegal number-> ", STDERR_FILENO);
			print(tok_command[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(commands);
			free(line);
			free(tok_command);
			exit(agg);
		}
	}
	else
		print("$  Exit can not admit further than one input", STDERR_FILENO);
}

/**
 *env - prints the present working environnement
 *@tok_command: command entered
 *
 *Return: void
 */

void env(char **tok_command __attribute__((unused)))
{
	int h;

	for (h = 0; environ[h] != NULL; h++)
	{
		print(environ[h], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}
