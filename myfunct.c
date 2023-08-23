#include "myheader.h"

/**
 * AUTHOR: Gentle Okhai
 * non_interactive - Deals with the non interactive aspect of the project
 *
 * Return: void
 */

void non_interactive(void)
{
    /*The declarations*/
	char **current_cmd = NULL;
	int i, type_cmd = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
        /*While loop*/
		while (getline(&line, &n, stdin) != -1)
		{
			remove_newline(line);
			remove_comment(line);
			commands = tokenizer(line, ";");
			for (i = 0; commands[i] != NULL; i++)
			{
				current_cmd = tokenizer(commands[i], " ");
				if (current_cmd[0] == NULL)
				{
					free(current_cmd);
					break;
				}
				type_cmd = parse_command(current_cmd[0]);
				initializer(current_cmd, type_cmd);
				free(current_cmd);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}

/**
 * initializer - begins execution 
 * @current_command: To inspect the current token
 * @type_command: parse token
 *
 * Return: void function
 */
void initializer(char **current_command, int type_command)
{
	pid_t PID;

    /*Control flow if!!!*/
	if (type_command == EXTERNAL_COMMAND || type_command == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
			execute_command(current_command, type_command);
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(current_command, type_command);
}
