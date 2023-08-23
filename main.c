#include "myheader.h"


	char **commands = NULL;
	char *line = NULL;
	char *shell_name = NULL;
	int status = 0;

/**
 * AUTHOR: Gentle Okhai
 * main - the main code for the shell
 * @argc: amount of arguments inputed
 * @argv: program arguments to be parsed
 *
 * applies the functions in utils and helpers
 * implements EOF
 * Prints error on Failure
 * Return: 0 on success
 */

int main(int argc __attribute__((unused)), char **argv)
{
    int j, type_command = 0;
	char **current_cmd = NULL;
	size_t n = 0;

	signal(SIGINT, ctrl_c_handler);
	shell_name = argv[0];
	while (1)
	{
		non_interactive();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&line, &n, stdin) == -1)
		{
			free(line);
			exit(status);
		}
			remove_newline(line);
			remove_comment(line);
			commands = tokenizer(line, ";");

		for (j = 0; commands[j] != NULL; j++)
		{
			current_cmd = tokenizer(commands[j], " ");
			if (current_cmd[0] == NULL)
			{
				free(current_cmd);
				break;
			}
			type_command = parse_command(current_cmd[0]);

			/* The initializing function -   */
			initializer(current_cmd, type_command);
			free(current_cmd);
		}
		free(commands);
	}
	free(line);

	return (status);
}
